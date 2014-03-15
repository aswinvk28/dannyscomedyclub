<?php

class QuoteCRUD {
    public static function get_entity($form_state) {
        $quotes = NULL;
        if(isset($form_state['node'])) {
            $node = $form_state['node'];
            $quotes = &entityfunctionality_set_entity_reference_node('pressquotation', $node);
        } elseif(isset($form_state['entity'])) {
            $entity = $form_state['entity'];
            $quotes = &entityfunctionality_set_entity_reference_node_entity('pressquotation', $entity);
        }
        if(empty($quotes)) {
            $quotes = entity_get_controller('pressquotation')->create(array());
        }
        return $quotes;
    }
    
    static public function pressquotation_form(&$form, &$form_state, $form_id) {
        $quotes = self::get_entity($form_state);
        if (!empty($quotes)) {
            
            $form['entity_quote'] = array(
                '#tree' => TRUE,
                '#type' => 'fieldset',
                '#title' => t('Quote Fields'),
                '#collapsible' => TRUE,
                '#collapsed' => TRUE,
                '#group' => 'visibility',
            );
            
            if(is_object($quotes)) {
                $form['entity_quote'] += pressquotation_fields_node_replicate($form, $form_state, $quotes);
            } else {
                foreach($quotes as $quote_id => $quote) {
                    $quotes[$quote_id]->getQuote();
                    $form['entity_quote'] = array_merge($form['entity_quote'], pressquotation_fields_node_replicate($form, $form_state, $quote, FALSE, '_'.$quote_id)); // load the quote fields
                }
            }
            
            if(!empty($form_state['values']['entity_quote']['quote_add'])) {
                $form['entity_quote'] += pressquotation_fields_node_replicate($form, $form_state, entity_get_controller('pressquotation')->create(array()));
            }
            
            $form['entity_quote']['quote_add'] = array(
                '#type' => 'select',
                '#ajax' => array(
                    'callback' => 'pressquotation_fields_node_add',
                    'event' => 'change',
                    'effect' => 'fade',
                    'method' => 'html',
                    'wrapper' => 'quote-fields-wrapper'
                ),
                '#options' => array(
                    'add' => t('Add')
                ),
                '#default_value' => '',
                '#empty_value' => '',
                '#empty_option' => 'None Selected',
                '#title' => t('Select the Action'),
                '#description' => t('Select which action to execute'),
            );
            
            $form['entity_quote']['quote_fields_wrapper'] = array(
                '#type' => 'html_tag',
                '#tag' => 'div',
                '#attributes' => array('id' => 'quote-fields-wrapper')
            );
            
        }
    }
}

?>