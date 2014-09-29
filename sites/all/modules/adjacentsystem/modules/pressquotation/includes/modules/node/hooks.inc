<?php

function pressquotation_node_insert($node) {
    if($node->type == 'artistes' || $node->type == 'shows' || $node->type == 'performances') {
        pressquotation_fields_node_submit($node, 'node');
    }
}

function pressquotation_node_update($node) {
    if($node->type == 'artistes' || $node->type == 'shows' || $node->type == 'performances') {
        pressquotation_fields_node_submit($node, 'node');
    }
}

function pressquotation_form_shows_node_form_alter(&$form, &$form_state, $form_id) {
    QuoteCRUD::pressquotation_form($form, $form_state, $form_id);
}

function pressquotation_form_artistes_node_form_alter(&$form, &$form_state, $form_id) {
    QuoteCRUD::pressquotation_form($form, $form_state, $form_id);
}

function pressquotation_form_performances_node_form_alter(&$form, &$form_state, $form_id) {
    QuoteCRUD::pressquotation_form($form, $form_state, $form_id);
}

function pressquotation_form_show_form_alter(&$form, &$form_state, $form_id) {
    $form_state['entity'] = $form_state['show'];
    QuoteCRUD::pressquotation_form($form, $form_state, $form_id);
    $form['#submit'][] = 'pressquotation_fields_entity_submit';
}

function pressquotation_form_performer_form_alter(&$form, &$form_state, $form_id) {
    $form_state['entity'] = $form_state['performer'];
    QuoteCRUD::pressquotation_form($form, $form_state, $form_id);
    $form['#submit'][] = 'pressquotation_fields_entity_submit';
}

function pressquotation_form_performance_form_alter(&$form, &$form_state, $form_id) {
    $form_state['entity'] = $form_state['performance'];
    QuoteCRUD::pressquotation_form($form, $form_state, $form_id);
    $form['#submit'][] = 'pressquotation_fields_entity_submit';
}

?>