<?php

function performance_form($form, $form_state, $entity, $op) {
    $node = (object) array('type' => 'performances');
    $form = PerformanceCRUD::performance_entity_form(array(), $form_state, $entity, $node);
    $form['performance_save'] = array(
        '#type' => 'submit',
        '#title' => t('Submit Entries'),
        '#value' => t('Save'),
        '#weight' => 14
    );
    return $form;
}

function performance_form_validate($form, $form_state) {
    $array = EventEntityWrapper::data($form_state['values']) + PerformanceEntityWrapper::data($form_state['values']);
    $object = (object) $array;
    performances_content_validate($object);
}

function performance_form_submit(&$form, $form_state) {
    
    $entity = $form_state['performance'];
    
    global $user;
    
    $node = array(
        'status' => 0,
        'type' => 'performances',
        'title' => $form_state['values']['title'],
        'uid' => $user->uid,
        'language' => 'und'
    );
    
    if(is_null($entity->getEntityId())) {
        $node['is_new'] = TRUE;
    } else {
        $node += array(
            'is_new' => FALSE,
            'nid' => $entity->getBundle(),
            'vid' => $entity->getBundleNode()->vid,
            'entity_node_bundle_id' => $entity->getBundle(),
            'entity_node_venue_id' => (array_key_exists('entity_node_venue_id', $form_state['values']) 
                    && !empty($form_state['values']['entity_node_venue_id'])) ? $form_state['values']['entity_node_venue_id'] : NULL
        );
    }
    
    $node += EventEntityWrapper::data($form_state['values']) + PerformanceEntityWrapper::data($form_state['values']);
    
    $node = (object) $node;
    $bool = node_save($node);
}

?>