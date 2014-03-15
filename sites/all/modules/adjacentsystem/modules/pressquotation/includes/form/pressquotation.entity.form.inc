<?php 

function pressquotation_fields_node_replicate($form, $form_state, $quote, $field_required = FALSE, $quote_id = '_plus', $ajax = FALSE) {
    $author = taxonomy_vocabulary_machine_name_load('author');
    $agency = taxonomy_vocabulary_machine_name_load('agency');
    
    $fields = array();
    
    $fields['entity_taxonomy_author_id'.$quote_id] = array(
        '#type' => 'select',
        '#title' => t('Author Name'),
        '#default_value' => !is_null($quote->getAuthor()) ? $quote->getAuthor() : '',
        '#empty_value' => '',
        '#empty_option' => 'None Selected',
        '#options' => !empty($author) ? taxonomy_allowed_values(array(
            'settings' => array(
                'allowed_values' => array(
                    array(
                        'vocabulary' => 'author',
                        'parent' => 0
                    )
                )
            )
        )) : array(),
        '#required' => FALSE,
        '#description' => t('The Name of the Author')
    );

    $fields['entity_taxonomy_agency_id'.$quote_id] = array(
        '#type' => 'select',
        '#title' => 'Agency',
        '#default_value' => !is_null($quote->getAgency()) ? $quote->getAgency() : NULL,
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
        '#required' => FALSE,
        '#description' => t('The Agency Vocabulary term')
    );

    $fields['quote'.$quote_id] = array(
        '#type' => 'textarea',
        '#title' => 'Quote Body',
        '#default_value' => !is_null($quote->getQuoteBody()) ? $quote->getQuoteBody() : '',
        '#required' => $field_required,
        '#description' => t('The content of Quote')
    );

    $fields['quote_date'.$quote_id] = array(
        '#type' => 'date_select',
        '#title' => 'Quote Date',
        '#default_value' => !is_null($quote->getDate()) ? $quote->getDate() :'',
        '#description' => t('The Date of the Quote')
    );
    
    if($ajax) {
        foreach($fields as $key => $field) {
            $index = 'entity_quote['.$key.']';
            $fields[$index] = $field;
            $fields[$index]['#attributes'] = array('name' => $index);
            unset($fields[$key]);
        }
        $fields['entity_quote[quote'.$quote_id.']']['#value'] = !empty($form_state['values']['entity_quote']['quote'.$quote_id]) ? 
            $form_state['values']['entity_quote']['quote'.$quote_id] : !is_null($quote->getQuoteBody()) ? $quote->getQuoteBody() : '';
        $fields['entity_quote[quote_date'.$quote_id.']']['#id'] = 'quote-date-plus';
    }
    
    return $fields;
    
}

function pressquotation_fields_node_submit($node) {
    $quotes = QuoteCRUD::get_entity(array(
        'node' => $node
    ));
    $transaction = db_transaction();
    try {
        if(is_array($quotes) && !empty($quotes)) {
            foreach($quotes as $quote_id => $quote) {
                $entity_id = $quote_id;
                $quote_id = '_'.$quote_id;
                if(empty($node->entity_quote['quote'.$quote_id])) {
                    $save_array = array(
                        'is_new' => FALSE,
                        'pressquotation_id' => $entity_id
                    );
                    $del_quote = entity_get_controller('pressquotation')->create($save_array);
                    $del_quote->delete();
                } else {
                    if($node->entity_quote['quote'.$quote_id] != $quote->quote || 
                            $node->entity_quote['entity_taxonomy_author_id'.$quote_id] != $quote->entity_taxonomy_author_id || 
                                    $node->entity_quote['entity_taxonomy_agency_id'.$quote_id] != $quote->entity_taxonomy_agency_id) 
                    {
                        $save_array = array(
                            'is_new' => FALSE,
                            'pressquotation_id' => $entity_id,
                            'entity_node_reference_id' => $node->nid,
                        );
                        $save_array += QuoteEntityWrapper::data(array(
                            'entity_taxonomy_agency_id' => $node->entity_quote['entity_taxonomy_agency_id'.$quote_id],
                            'entity_taxonomy_author_id' => $node->entity_quote['entity_taxonomy_author_id'.$quote_id],
                            'quote' => $node->entity_quote['quote'.$quote_id],
                            'quote_date' => $node->entity_quote['quote_date'.$quote_id]
                        ));

                        $quote = entity_get_controller('pressquotation')->create($save_array);
                        $quote->save();
                    }
                }
            }
        }

        if(!empty($node->entity_quote['quote_plus'])) {
            $save_array = array(
                'is_new' => TRUE,
                'entity_node_reference_id' => $node->nid,
            );
            $save_array += QuoteEntityWrapper::data(array(
                'entity_taxonomy_agency_id' => $node->entity_quote['entity_taxonomy_agency_id_plus'],
                'entity_taxonomy_author' => $node->entity_quote['entity_taxonomy_author_id_plus'],
                'quote' => $node->entity_quote['quote_plus'],
                'quote_date' => $node->entity_quote['quote_date_plus']
            ));

            $quote = entity_get_controller('pressquotation')->create($save_array);
            $quote->save();
        }
    } catch(Exception $e) {
        $transaction->rollback();
    }
}

function pressquotation_formfields_node_validate($node) {
    $quotes = QuoteCRUD::get_entity(array(
        'node' => $node
    ));
    if(is_array($quotes) && !empty($quotes)) {
        foreach($quotes as $quote_id => $quote) {
            pressquotation_fields_node_validate($node, '_'.$quote_id);
        }
    }
    if(!empty($node->quote_plus)) {
        pressquotation_fields_node_validate($node);
    }
}

function pressquotation_fields_node_validate($node, $quote_id = '_plus') {
    if(!empty($node->entity_quote['entity_taxonomy_author_id'.$quote_id])) {
        $term1 = taxonomy_term_load($node->entity_quote['entity_taxonomy_author_id'.$quote_id]);

        if(!empty($term1) && empty($term1->name)) {
            form_set_error('entity_taxonomy_author_id'.$quote_id, 'Select valid Author');
        } else {
            $vocab1 = taxonomy_vocabulary_machine_name_load('author');
            if($term1->vid !== $vocab1->vid) {
                form_set_error('entity_taxonomy_author_id'.$quote_id, 'Select valid Author');
            }
        }
    }
    
    if(!empty($node->entity_quote['quote'.$quote_id]) && !drupal_validate_utf8($node->entity_quote['quote'.$quote_id])) {
        form_set_error('quote'.$quote_id, 'Enter valid Quote Body');
    }
    
    if(!empty($node->entity_quote['entity_taxonomy_agency_id'.$quote_id])) {
        $term2 = taxonomy_term_load($node->entity_quote['entity_taxonomy_agency_id'.$quote_id]);
        if(!empty($term2) && empty($term2->name)) {
            form_set_error('entity_taxonomy_agency_id'.$quote_id, 'Select valid Agency');
        } else {
            $vocab2 = taxonomy_vocabulary_machine_name_load('agency');
            if($term2->vid !== $vocab2->vid) {
                form_set_error('entity_taxonomy_agency_id'.$quote_id, 'Select valid Agency');
            }
        }
    }
}

?>