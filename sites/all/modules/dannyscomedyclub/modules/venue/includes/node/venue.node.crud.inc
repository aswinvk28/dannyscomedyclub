<?php

function venue_content_insert($node) {
    $document = entity_get_controller('document')->create(array(
        'file_path' => 'venue',
        'file_type' => array('text/html', 'html'),
    )); // document_type for file path value
    if(!empty($node->document_body)) {
        $document->createFile($node->document_body);
        $document->save();
    }
    
    $save_array = array(
        'entity_document_id' => !is_null($document->getEntityId()) ? $document->getEntityId() : NULL,
        'entity_node_bundle_id' => $node->nid,
    );
    $save_array += VenueEntityWrapper::data(array(
        'venue_address' => $node->venue_address,
        'venue_location' => $node->venue_location,
        'venue_telephone' => $node->venue_telephone,
        'venue_geo_lat' => $node->venue_geo_lat,
        'venue_geo_long' => $node->venue_geo_long,
        'venue_url' => $node->venue_url
    ));
    
    $venue = entity_get_controller('venue')->create($save_array);
    $venue->save();
}

function venue_content_update($node) {
    $entity = entityfunctionality_set_entity_bundle_node('venue', $node);
    
    $document = entity_get_controller('document')->create(array(
        'is_new' => FALSE,
        'document_id' => $entity->getParentEntity()->getEntityId(),
        'document_file_id' => $entity->getParentEntity()->getFile(),
        'file_path' => 'venue',
        'file_type' => array('text/html', 'html')
    ));
    if($document->getDocumentBody() !== $node->document_body) {
        if(!$document->saveFile($node->document_body)) {
            $document->delete();
            $document->document_id = NULL;
        }
    }
    
    $save_array = array(
        'entity_document_id' => !is_null($document->getEntityId()) ? $document->getEntityId() : NULL,
        'entity_node_bundle_id' => $node->nid,'is_new' => FALSE,
        'venue_id' => $entity->getEntityId(),
        'entity_node_bundle_id' => $node->nid,
    );
    $save_array += VenueEntityWrapper::data(array(
        'venue_address' => $node->venue_address,
        'venue_location' => $node->venue_location,
        'venue_telephone' => $node->venue_telephone,
        'venue_geo_lat' => $node->venue_geo_lat,
        'venue_geo_long' => $node->venue_geo_long,
        'venue_url' => $node->venue_url
    ));
    
    $venue = entity_get_controller('venue')->create($save_array);
    $venue->save();
}

function venue_content_delete($node) {
    $entity = entityfunctionality_set_entity_bundle_node('venue', $node);
    
    $transaction = db_transaction();
    
    try {
        $venue = entity_get_controller('venue')->create(array(
            'venue_id' => $entity->getEntityId()
        ));
        $venue->save();
        
        $document = entity_get_controller('document')->create(array(
            'is_new' => FALSE,
            'document_id' => $entity->getParentEntity()->getEntityId(),
        ));
        $document->delete();

    } catch (Exception $e) {
        $transaction->rollback();
    }
    
}

?>