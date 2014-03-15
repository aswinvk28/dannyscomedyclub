<?php

function pressquotation_entity_info() {
    
    return array(
        'pressquotation' => array(
            'label' => t('Press Quote'),
            'uri_callback' => 'pressquotation_uri',
            'controller class' => 'QuoteController',
            'entity class' => 'QuoteEntity',
            'base table' => 'dcc_entity_pressquotation',
            'static cache' => TRUE,
            'field cache' => FALSE,
            'entity cache' => TRUE,
            'fieldable' => FALSE,
            'entity keys' => array(
                'id' => 'pressquotation_id'
            ),
            'view modes' => array(
                'full' => array(
                  'label' => t('Full content'),
                  'custom settings' => FALSE,
                ),
                'general_view' => array(
                    'label' => t('General View')
                )
            )
        )
    );
    
}

?>