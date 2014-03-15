<?php

function performer_entity_info() {
    $performer_entity = array(
        'performer' => array(
            'label' => t('Performer'),
            'base table' => 'dcc_entity_performer',
            'fieldable' => FALSE,
            'field cache' => FALSE,
            'static cache' => TRUE,
            'entity cache' => TRUE,
            'entity keys' => array(
                'id' => 'performer_id'
            ),
            'controller class' => 'PerformerController',
            'entity class' => 'PerformerEntity',
            'label callback' => 'entity_node_label',
            'uri callback' => 'dcc_entity_node_uri',
            'access callback' => 'dannyscomedyclub_entity_access',
            'bundles' => array(
                'artistes' => array(
                    'label' => t('Artistes')
                ),
                'groups' => array(
                    'label' => t('Groups')
                )
            ),
            'view modes' => array(
                'full' => array(
                    'label' => t('Full content'),
                    'custom settings' => FALSE,
                ),
                'performer_view' => array(
                    'label' => t('Performer View')
                ),
                'performer_view_scaled_down' => array(
                    'label' => t('Performer View Scaled Down')
                )
            ),
            'admin ui' => array(
                'path' => 'admin/performer',
                'menu wildcard' => '%entity_object',
                'file path' => drupal_get_path('module', 'entity'),
                'file' => 'includes/entity.ui.inc'
            )
        )
    );
    
    return $performer_entity;
}

function performer_entity_info_alter(&$entity_info) {
    $entity_info['node']['bundles']['artistes']['uri callback'] = 'dannyscomedyclub_uri';
}

?>