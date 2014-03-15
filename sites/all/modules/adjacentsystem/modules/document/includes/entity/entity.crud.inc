<?php

class DocumentCRUD {
    static public function document_mini_form(&$form, $document) {
        $form['document'] = array(
            '#type' => 'fieldset',
            '#title' => t('Document'),
            '#description' => t('Enter Document Fields'),
            '#collapsible' => TRUE,
            '#collapsed' => TRUE,
            '#group' => 'addtional_settings'
        );
        
        $form['document']['document_body'] = array(
            '#type' => 'textarea',
            '#title' => t('Body of the document'),
            '#description' => t('Enter the body of the document'),
            '#required' => TRUE,
            '#default_value' => !is_null($document->getDocumentBody()) ? $document->getDocumentBody() : ''
        );
    }
    
    static function document_form(&$form, $document) {
        self::document_mini_form($form, $document);
        
        $form['document']['document_author'] = array(
            '#type' => 'textfield',
            '#title' => t('Document Author'),
            '#description' => t('Enter the name of the author'),
            '#required' => FALSE,
            '#default_value' => !is_null($document->getAuthor()) ? $document->getAuthor() : ''
        );
    }
}

?>
