<?php

function shows_content_form($node, &$form_state) {
    $form = array();
    $node = $form_state['node'];
    ShowCRUD::show_node_form($form, $form_state, $node);
    return $form;
}

function shows_content_validate($node) {
    EventCRUD::event_form_validate($node);
    if(module_exists('pressquotation')) {
        module_invoke('pressquotation', 'formfields_node_validate', $node);
    }
}

function show_form_shows_node_form_alter(&$form, &$form_state, $form_id) {
    $form['#submit'][] = 'show_node_form_submit';
}

?>