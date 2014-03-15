<?php

function venue_entity_info() {
    
    $venue_entity = array(
        'venue' => array(
            'label' => t('Venue'),
            'uri callback' => 'dcc_entity_node_uri',
            'controller class' => 'VenueController',
            'entity class' => 'VenueEntity',
            'base table' => 'dcc_entity_venue',
            'field cache' => FALSE,
            'static cache' => TRUE,
            'entity cache' => TRUE,
            'fieldable' => FALSE,
            'access callback' => 'dannyscomedyclub_entity_access',
            'label callback' => 'entity_node_label',
            'entity keys' => array(
                'id' => 'venue_id'
            ),
            'bundles' => array(
                'venue' => array(
                    'label' => t('Venue')
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
            ),
            'admin ui' => array(
                'path' => 'admin/venue',
                'menu wildcard' => '%entity_object',
                'file path' => drupal_get_path('module', 'entity'),
                'file' => 'includes/entity.ui.inc'
            )
        )
    );
    
    return $venue_entity;
    
}

?>