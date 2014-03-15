<?php

function venue_form($form, $form_state, $entity, $op) {
    $node = (object) array('type' => 'venue');
    $form = VenueCRUD::venue_entity_form(array(), $form_state, $entity, $node);
    $form['venue_save'] = array(
        '#type' => 'submit',
        '#title' => t('Submit Entries'),
        '#value' => t('Save'),
        '#weight' => 14
    );
    return $form;
}

function venue_form_validate($form, $form_state) {
    $object = (object) VenueEntityWrapper::data($form_state['values']);
    venue_content_validate($object);
}

function venue_form_submit(&$form, $form_state) {
    
    $entity = $form_state['venue'];
    
    global $user;
    
    $node = array(
        'status' => 0,
        'type' => 'venue',
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
        $node['entity_document_id'] = $entity->getDocument();
    }
    
    $node = array_merge($node, VenueEntityWrapper::data($form_state['values']));
    
    $node = (object) $node;
    $bool = node_save($node);
}

?>