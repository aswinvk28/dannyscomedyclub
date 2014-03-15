<?php

function artistes_content_insert($node) {
    $transaction = db_transaction();
    try {
        $save_array = array(
            'entity_node_bundle_id' => $node->nid
        );
        $save_array += PerformerEntityWrapper::data(array(
            'performer_email' => $node->performer_email,
            'performer_fb' => $node->performer_fb,
            'performer_twitter' => $node->performer_twitter,
            'performer_yt' => $node->performer_yt,
            'performer_website' => $node->performer_website,
            'performer_opt' => !empty($node->performer_opt) ? $node->performer_opt : NULL
        ));
        
        $artiste = entity_get_controller('performer')->create($save_array);
        $artiste->save();
        
    } catch(Exception $e) {
        $transaction->rollback();
    }
}

function artistes_content_update($node) {
    $transaction = db_transaction();
    try {
        $entity = entityfunctionality_set_entity_bundle_node('performer', $node);
        
        $save_array = array(
            'is_new' => FALSE,
            'entity_node_bundle_id' => $node->nid,
            'performer_id' => $entity->getEntityId(),
        );
        $save_array += PerformerEntityWrapper::data(array(
            'performer_email' => $node->performer_email,
            'performer_fb' => $node->performer_fb,
            'performer_twitter' => $node->performer_twitter,
            'performer_yt' => $node->performer_yt,
            'performer_website' => $node->performer_website,
            'performer_opt' => !empty($node->performer_opt) ? $node->performer_opt : NULL
        ));

        $artiste = entity_get_controller('performer')->create($save_array, 'performer');
        $artiste->save();
        
    } catch(Exception $e) {
        $transaction->rollback();
    }
}

function artistes_content_delete($node) {
    $transaction = db_transaction();
    try {
        $entity = entityfunctionality_set_entity_bundle_node('performer', $node);
        $entity->delete();
    } catch(Exception $e) {
        $transaction->rollback();
    }
}

?>