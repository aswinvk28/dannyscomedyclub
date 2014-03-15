<?php

function performances_content_insert($node) {
    $transaction = db_transaction();
    try {
        $event_save_array = array(
            'is_new' => TRUE,
            'event_bundle' => 'performance'
        );
        $event_save_array += EventEntityWrapper::data(array(
            'event_name' => $node->event_name,
            'event_url' => $node->event_url,
            'image_caption' => $node->image_caption,
            'event_image_file_id' => $node->event_image_file_id,
            'event_image_event_id' => $node->event_image_event_id,
            'entity_taxonomy_event_status_id' => $node->entity_taxonomy_event_status_id,
            'event_date' => $node->event_date
        ));
        $event = entity_get_controller('event')->create($event_save_array);
        $event->save();

        $performance_save_array = array(
            'is_new' => TRUE,
            'entity_node_bundle_id' => $node->nid,
            'entity_event_id' => $event->getEntityId()
        );
        $performance_save_array += PerformanceEntityWrapper::data(array(
            'entity_node_shows_id' => $node->entity_node_shows_id,
            'entity_performer_id' => $node->entity_performer_id,
            'entity_taxonomy_performances_types_id' => $node->entity_taxonomy_performances_types_id,
            'performance_order' => $node->performance_order,
            'performance_video' => $node->performance_video
        ));
        $performance = entity_get_controller('performance')->create($performance_save_array);
        $performance->save();
    } catch(Exception $e) {
        $transaction->rollback();
    }
}

function performances_content_update($node) {
    $transaction = db_transaction();
    try {
        $entity = entityfunctionality_set_entity_bundle_node('performance', $node);
        
        $event_save_array = array(
            'is_new' => FALSE,
            'event_id' => $entity->getEvent(),
            'event_bundle' => 'performance'
        );
        $event_save_array += EventEntityWrapper::data(array(
            'entity_taxonomy_event_status_id' => $node->entity_taxonomy_event_status_id,
            'event_name' => $node->event_name,
            'image_caption' => $node->image_caption,
            'event_url' => $node->event_url,
            'event_image_file_id' => $node->event_image_file_id,
            'event_image_event_id' => $node->event_image_event_id,
            'event_date' => $node->event_date
        ));
        $event = entity_get_controller('event')->create($event_save_array);
        $event->save();
        
        $performance_save_array = array(
            'is_new' => FALSE,
            'performance_id' => $entity->getEntityId(),
            'entity_node_bundle_id' => $node->nid,
            'entity_event_id' => $event->getEntityId()
        );
        $performance_save_array += PerformanceEntityWrapper::data(array(
            'entity_node_shows_id' => $node->entity_node_shows_id,
            'entity_performer_id' => $node->entity_performer_id,
            'entity_taxonomy_performances_types_id' => $node->entity_taxonomy_performances_types_id,
            'performance_order' => $node->performance_order,
            'performance_video' => $node->performance_video
        ));
        $performance = entity_get_controller('performance')->create($performance_save_array);
        $performance->save();
    } catch(Exception $e) {
        $transaction->rollback();
    }
}

function performances_content_delete($node) {
    $entity = entityfunctionality_set_entity_bundle_node('performance', $node);
    $transaction = db_transaction();
    try {
        $entity->delete();
    } catch(Exception $e) {
        $transaction->rollback();
    }
}

function performance_node_form_submit($form, &$form_state) {
    $transaction = db_transaction();
    try {
        $event_status = $form_state['values']['entity_taxonomy_event_status_id'];

        $status_term = taxonomy_term_load($event_status);
        if($status_term->name == 'cancelled') {
            $form_state['values']['status'] = 0;
        }
    } catch(Exception $e) {
        $transaction->rollback();
    }
}

?>