<?php

function review_form_submit($form, $form_state) {
    $object = (object) NodeDocumentReferenceEntityWrapper::data($form_state['values']);
    
    $entity = $form_state['review'];
    
    if(is_null($entity->getEntityId())) {
        $document = entity_get_controller('document')->create(array(
            'file_path' => 'external',
            'file_type' => array('text/html', 'html'),
            'document_author' => $object->document_author
        )); // document_type for file path value
        if(!empty($object->document_body)) {
            $document->createFile($object->document_body);
            $document->save();
        }

        $review_save_array = array(
            'is_new' => TRUE,
            'entity_node_reference_id' => $object->entity_node_reference_id,
            'entity_document_id' => $document->getEntityId(),
            'entity_taxonomy_agency_id' => $object->entity_taxonomy_agency_id,
            'ndreference_name' => $object->ndreference_name,
            'ndreference_date' => $object->ndreference_date,
            'ndreference_bundle' => 'review'
        );
        $review = entity_get_controller('review')->create($review_save_array);
        $review->save();
    } else {
        $document = entity_get_controller('document')->create(array(
            'is_new' => FALSE,
            'document_id' => $entity->getParentEntity()->getEntityId(),
            'document_file_id' => $entity->getParentEntity()->getFile(),
            'document_author' => $object->document_author,
            'file_path' => 'external',
            'file_type' => array('text/html', 'html')
        ));
        if($document->getDocumentBody() !== $object->document_body) {
            if(!$document->saveFile($object->document_body)) {
                $document->delete();
                $document->document_id = NULL;
            }
        }

        $review_save_array = array(
            'is_new' => FALSE,
            'ndreference_id' => $entity->getEntityId(),
            'entity_node_reference_id' => $object->entity_node_reference_id,
            'entity_document_id' => $document->getEntityId(),
            'entity_taxonomy_agency_id' => $object->entity_taxonomy_agency_id,
            'ndreference_name' => $object->ndreference_name,
            'ndreference_date' => $object->ndreference_date,
            'ndreference_bundle' => $entity->getBundleString()
        );
        $review = entity_get_controller('review')->create($review_save_array);
        $review->save();
    }
}

?>