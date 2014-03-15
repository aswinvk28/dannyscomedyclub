<?php

function review_form($form, &$form_state, $entity, $op) {
    $form_state['entity'] = $form_state['review'];
    $form = NodeDocumentReferenceCRUD::node_document_reference_entity_form(array(), $form_state, $form_state['review']);
    $form['review_save'] = array(
        '#type' => 'submit',
        '#title' => t('Submit Entries'),
        '#value' => t('Save'),
        '#weight' => 14
    );
    return $form;
}

function review_form_validate($form, $form_state) {
    $object = (object) NodeDocumentReferenceEntityWrapper::data($form_state['values']);
    document_fields_node_form_validate($object);
    
    if(!empty($object->ndreference_name) && !preg_match('/^[a-z\w\s\ \-\,\.A-Z]+$/', $object->ndreference_name)) {
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