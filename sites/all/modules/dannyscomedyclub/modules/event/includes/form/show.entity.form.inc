<?php

function show_form($form, $form_state, $entity, $op) {
    $node = (object) array('type' => 'shows');
    $form = ShowCRUD::show_entity_form(array(), $form_state, $entity, $node);
    $form['show_save'] = array(
        '#type' => 'submit',
        '#title' => t('Submit Entries'),
        '#value' => t('Save'),
        '#weight' => 14
    );
    return $form;
}

function show_form_validate($form, $form_state) {
    $object = (object) EventEntityWrapper::data($form_state['values']);
    shows_content_validate($object);
    $date_format = FALSE;
    if(is_string($form_state['values']['field_date'])) {
        $date = new DateTime($form_state['values']['field_date']);
        $date_format = $date->format('Y-m-d H:i:s');
    }
    if(!$date_format) {
        form_set_error('field_date', t('Select Valid Date'));
    }
}

function show_form_submit(&$form, $form_state) {
    
    $entity = $form_state['show'];
    
    global $user;
    
    $node = array(
        'status' => 0,
        'type' => 'shows',
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
        );
    }
    $node['entity_node_venue_id'] = !empty($form_state['values']['entity_node_venue_id']) ? $form_state['values']['entity_node_venue_id'] : NULL;
    
    $date = new DateTime($form_state['values']['field_date']);
    $date_format = $date->format('Y-m-d H:i:s');
    
    if($date_format) {
        $node['field_date'] = array(
            'und' => array(
                0 => array(
                    'value' => $date_format
                )
            )
        );
    }
    $node += EventEntityWrapper::data($form_state['values']);
    
    $save_node = (object) $node;
    if(!node_save($save_node)) {
        throw Exception(t('Node Not Saved'));
    }
}

?>