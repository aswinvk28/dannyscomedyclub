<?php

class NodeDocumentReferenceCRUD {
    public static function node_document_reference_entity_form($form, &$form_state, $entity) {
        $agency = taxonomy_vocabulary_machine_name_load('agency');
        
        DocumentCRUD::document_form($form, $entity->getParentEntity());
        
        $form['review_fields'] = array(
            '#type' => 'fieldset',
            '#title' => t('Node Document Reference Fields'),
            '#description' => t('Enter Review Fields'),
            '#collapsible' => TRUE,
            '#collapsed' => TRUE,
            '#group' => 'visibility'
        );
        
        $form['review_fields']['ndreference_name'] = array(
            '#type' => 'textfield',
            '#title' => t('Name'),
            '#description' => t('Enter the name'),
            '#required' => FALSE,
            '#default_value' => !empty($entity->ndreference_name) ? $entity->ndreference_name : ''
        );
        
        $form['review_fields']['entity_taxonomy_agency_id'] = array(
            '#type' => 'select',
            '#title' => t('Review Agency'),
            '#description' => t('Select the Agency which publishes the review'),
            'required' => FALSE,
            '#empty_value' => '',
            '#empty_option' => 'None Selected',
            '#options' => !empty($agency) ? taxonomy_allowed_values(array(
                'settings' => array(
                    'allowed_values' => array(
                        array(
                            'vocabulary' => 'agency',
                            'parent' => 0
                        )
                    )
                )
            )) : array(),
            '#default_value' => !is_null($entity->getAgency()) ? $entity->getAgency() : ''
        );
        
        $form['review_fields']['ndreference_date'] = array(
            '#type' => 'date_select',
            '#title' => 'Document Date',
            '#default_value' => !is_null($entity->getDate()) ? $entity->getDate() :'',
            '#description' => t('The Date of the Document')
        );
        
        $bundle_type = '';
        $bool = !empty($form_state['values']['ajax_node_bundle']);
        if(!is_null($entity->getReference())) {
            $bundle_type = node_load($entity->getReference())->type;
        }
        $form['review_fields']['ajax_node_bundle'] = array(
            '#type' => 'select',
            '#title' => t('Node Type'),
            '#description' => t('Select the Node Bundle Type'),
            '#empty_value' => '',
            '#empty_option' => 'None Selected',
            '#options' => array(
                'shows' => t('Shows'),
                'performances' => t('Performances'),
                'artistes' => t('Artistes'),
                'organisation' => t('Organisation')
            ),
            '#ajax' => array(
                'callback' => 'ndreference_add_reference_nodes_wrapper',
                'method' => 'html',
                'effect' => 'fade',
                'event' => 'change',
                'wrapper' => 'ndreference-reference-id-wrapper'
            ),
            '#required' => TRUE,
            '#default_value' => $bundle_type
        );
        
        $form['review_fields']['bundle_type_wrapper'] = array(
            '#type' => 'html_tag',
            '#tag' => 'div',
            '#attributes' => array('id' => 'ndreference-reference-id-wrapper')
        );
        
        if(!$bool) {
            $form['review_fields']['entity_node_reference_id'] = ndreference_add_reference_nodes($form, $form_state, $bundle_type); // set form for loading
        } else {
            $form['review_fields']['entity_node_reference_id'] = ndreference_add_reference_nodes($form, $form_state, $form_state['values']['ajax_node_bundle']); // initialise the form after submission
        }
        
        return $form;
    }
    
}

?>