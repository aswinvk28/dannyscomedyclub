<?php

function press_release_form($form, &$form_state, $entity, $op) {
    $form_state['entity'] = $form_state['press_release'];
    $form = NodeDocumentReferenceCRUD::node_document_reference_entity_form(array(), $form_state, $form_state['press_release']);
    $form['press_release_save'] = array(
        '#type' => 'submit',
        '#title' => t('Submit Entries'),
        '#value' => t('Save'),
        '#weight' => 14
    );
    return $form;
}

function press_release_form_validate($form, $form_state) {
    $object = (object) NodeDocumentReferenceEntityWrapper::data($form_state['values']);
    if(empty($object->document_body) || !drupal_validate_utf8($object->document_body)) {
        form_set_error('document_body', 'Enter valid strings for Document Body');
    }
    
    if(!empty($object->ndreference_name) && !preg_match("/^(\w+\d*[\'\-\,\.]*\s?)+/i", $object->ndreference_name)) {
        form_set_error('ndreference_name', 'Enter Review Name');
    }
    $term = taxonomy_term_load($object->entity_taxonomy_agency_id);
    $vocab = taxonomy_vocabulary_machine_name_load('agency');
    if(!empty($term) && ($term->vid !== $vocab->vid)) {
        form_set_error('entity_taxonomy_agency_id', 'Select Valid Agency');
    }
    
    if(!empty($object->ajax_node_bundle) && empty($object->entity_node_reference_id)) {
        form_set_error('entity_node_reference_id', t('Select Valid Node Type for the Review'));
    }
}

?>