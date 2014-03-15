<?php

function shows_content_insert($node) {
    $transaction = db_transaction();
    try {
        $event_save_array = array(
            'is_new' => TRUE,
            'event_bundle' => 'show'
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

        $shows_save_array = array(
            'entity_event_id' => $event->getEntityId(),
            'entity_node_bundle_id' => $node->nid,
            'entity_node_venue_id' => property_exists($node, 'entity_node_venue_id') && !empty($node->entity_node_venue_id) ? $node->entity_node_venue_id : NULL
        );

        $shows = entity_get_controller('show')->create($shows_save_array);
        $shows->save();
        
    } catch(Exception $e) {
        $transaction->rollback();
    }
}

function shows_content_update($node) {
    $transaction = db_transaction();
    try {
        $entity = entityfunctionality_set_entity_bundle_node('show', $node);
        $event_save_array = array(
            'is_new' => FALSE,
            'event_id' => $entity->getEvent(),
            'event_bundle' => 'show'
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

        $shows_save_array = array(
            'is_new' => FALSE,
            'show_id' => $entity->getEntityId(),
            'entity_event_id' => $event->getEntityId(),
            'entity_node_bundle_id' => $node->nid,
            'entity_node_venue_id' => !empty($node->entity_node_venue_id) ? $node->entity_node_venue_id : NULL
        );

        $shows = entity_get_controller('show')->create($shows_save_array);
        $shows->save();
        
    } catch(Exception $e) {
        $transaction->rollback();
    }
}

function show_node_form_submit(&$form, &$form_state) {
    global $user;
    
    $transaction = db_transaction();
    
    try {
        $event_status = $form_state['values']['entity_taxonomy_event_status_id'];
        $status_term = taxonomy_term_load((int) $event_status);
        $node = $form_state['node'];
        if(property_exists($node, 'nid') && isset($node->nid) && module_exists('performance')) {
            $entity = entityfunctionality_set_entity_bundle_node('show', $node);
            $performances = $entity->getPublishedPerformances();

            if(!empty($performances)) {
                if($status_term->name != 'TBC') {
                    foreach($performances as $performance) {
                        $event = $performance->getParentEntity();
                        $event->getImage();
                        $event->setEventStatus($status_term->tid);
                        $event_save_array = array(
                            'event_id' => $event->getEntityId(),
                            'is_new' => FALSE
                        );
                        $event_save_array += EventEntityWrapper::data(array(
                            'event_name' => $event->getName(),
                            'event_url' => $event->getUrl(),
                            'image_caption' => $event->getImageCaption(),
                            'event_image_file_id' => $event->getEventImage(),
                            'event_image_event_id' => $event->getPromoEvent(),
                            'entity_taxonomy_event_status_id' => $event->getEventStatus(),
                            'event_date' => $event->getDate()
                        ));
                        $event_save = entity_get_controller('event')->create($event_save_array);
                        $event_save->save();
                        if($status_term->name == 'Cancelled') {
                            $performance_node = array(
                                'nid' => $performance->getBundle(),
                                'vid' => node_load($performance->getBundle())->vid,
                                'status' => 0,
                                'is_new' => FALSE,
                                'type' => 'performances',
                                'uid' => $user->uid,
                                'language' => 'und'
                            );

                            node_save((object) $performance_node);
                        }
                    }
                }
            }
        }
        if($status_term->name == 'Cancelled') {
            $form_state['values']['status'] = 0;
        }
    } catch (Exception $e) {
        $transaction->rollback();
    }
}

?>