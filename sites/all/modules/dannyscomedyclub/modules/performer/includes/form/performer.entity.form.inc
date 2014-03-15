<?php

function performer_form($form, $form_state, $entity, $op) {
    $node = (object) array('type' => 'artistes');
    $form = PerformerCRUD::performer_entity_form(array(), $form_state, $entity, $node);
    $form['performer_save'] = array(
        '#type' => 'submit',
        '#title' => t('Submit Entries'),
        '#value' => t('Save'),
        '#weight' => 14
    );
    return $form;
}

function performer_form_validate($form, $form_state) {
    $object = (object) PerformerEntityWrapper::data($form_state['values']);
    artistes_content_validate($object);
}

function performer_form_submit(&$form, $form_state) {
    
    $entity = $form_state['performer'];
    
    global $user;
    
    $node = array(
        'status' => 0,
        'type' => 'artistes',
        'title' => $form_state['values']['title'],
        'uid' => $user->uid,
        'language' => 'und'
    );
    
    if(is_null($entity->getEntityId())) {
        $node['is_new'] = TRUE;
    } else {
        $node['is_new'] = FALSE;
        $node['nid'] = $entity->getBundle();
        $node['vid'] = $entity->getBundleNode()->vid;
        $node['entity_node_bundle_id'] = $entity->getBundle();
    }
    
    $node += PerformerEntityWrapper::data($form_state['values']);
    
    $node = (object) $node;
    $bool = node_save($node);
}

?>