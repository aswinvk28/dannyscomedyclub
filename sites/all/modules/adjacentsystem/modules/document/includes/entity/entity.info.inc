<?php

function document_entity_info() {
    return array(
        'document' => array(
            'label' => t('Document'),
            'controller class' => 'DocumentController',
            'entity class' => 'DocumentEntity',
            'base table' => 'dcc_entity_document',
            'field cache' => FALSE,
            'static cache' => TRUE,
            'entity cache' => TRUE,
            'fieldable' => FALSE,
            'entity keys' => array(
                'id' => 'document_id'
            ),
            'bundles' => array(
                'ndreference' => array(
                    'label' => t('Node Document Reference')
                )
            ),
            'view modes' => array(
                'full' => array(
                  'label' => t('Full content'),
                  'custom settings' => FALSE,
                ),
                'teaser' => array(
                  'label' => t('Teaser'),
                  'custom settings' => TRUE,
                ),
                'rss' => array(
                  'label' => t('RSS'),
                  'custom settings' => FALSE,
                ),
            )
        )
    );
}

?>