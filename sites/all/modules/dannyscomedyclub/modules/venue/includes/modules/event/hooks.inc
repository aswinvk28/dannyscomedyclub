<?php

function venue_form_show_form_alter(&$form, &$form_state, $form_id) {
    $entity = $form_state['show'];
    
    VenueCRUD::venue_show_entity_form($form, $form_state, $entity);
}

function venue_form_shows_node_form_alter(&$form, &$form_state, $form_id) {
    $node = $form_state['node'];
    $entity = entityfunctionality_set_entity_bundle_node('show', $node);
    
    VenueCRUD::venue_show_entity_form($form, $form_state, $entity);
}

function venue_shows_node_form_validate($form, &$form_state) {
    $nodes = node_load_multiple(array(), array(
        'type' => 'venue'
    ));
    if(!array_key_exists($form_state['values']['entity_node_venue_id'], $nodes)) {
        form_set_error('entity_node_venue_id', t('Check the Venue Selected Node Value'));
    }
}

?>