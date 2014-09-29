<?php

class QuoteCRUD {
    public static $quotes = NULL;
    
    public static function get_entity($form_state) {
        if(is_null(self::$quotes)) {
            if(isset($form_state['node'])) {
                $node = $form_state['node'];
                self::$quotes = entityfunctionality_set_entity_reference_node('pressquotation', $node);
            } elseif(isset($form_state['entity'])) {
                $entity = $form_state['entity'];
                self::$quotes = entityfunctionality_set_entity_reference_node_entity('pressquotation', $entity);
            }
            if(empty(self::$quotes)) {
                self::$quotes = entity_get_controller('pressquotation')->create(array());
            }
        }
        return self::$quotes;
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
                $form['entity_quote'] += pressquotation_fields_node_replicate($form, $form_state, $quotes, FALSE, '_plus');
            } else {
                foreach($quotes as $quote_id => $quote) {
                    QuoteCRUD::$quotes[$quote_id]->getQuote();
                    $form['entity_quote'] = array_merge($form['entity_quote'], pressquotation_fields_node_replicate($form, $form_state, QuoteCRUD::$quotes[$quote_id], FALSE, '_'.$quote_id)); // load the quote fields
                }
            }
            $count = is_array($quotes) ? count($quotes) : 1;
            for($index = 5; $index > $count; $index--) {
                $quote = entity_get_controller('pressquotation')->create(array());
                $form['entity_quote'] = array_merge($form['entity_quote'], pressquotation_fields_node_replicate($form, $form_state, $quote, FALSE, '_plus_'.$index));
            }
            
//            if(!empty($form_state['values']['entity_quote']['quote_add'])) {
//                $form['entity_quote'] += pressquotation_fields_node_replicate($form, $form_state, entity_get_controller('pressquotation')->create(array()));
//            }
//            
//            $form['entity_quote']['quote_add'] = array(
//                '#type' => 'select',
//                '#ajax' => array(
//                    'callback' => 'pressquotation_fields_node_add',
//                    'event' => 'change',
//                    'effect' => 'fade',
//                    'method' => 'html',
//                    'wrapper' => 'quote-fields-wrapper'
//                ),
//                '#options' => array(
//                    'add' => t('Add')
//                ),
//                '#default_value' => '',
//                '#empty_value' => '',
//                '#empty_option' => 'None Selected',
//                '#title' => t('Select the Action'),
//                '#description' => t('Select which action to execute'),
//            );
//            
//            $form['entity_quote']['quote_fields_wrapper'] = array(
//                '#type' => 'html_tag',
//                '#tag' => 'div',
//                '#attributes' => array('id' => 'quote-fields-wrapper')
//            );
            
        }
    }
}

?>