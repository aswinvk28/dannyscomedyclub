<?php

function event_entity_info() {
    $event_entity = array(
        'event' => array(
            'label' => t('Event'),
            'base table' => 'dcc_entity_event',
            'fieldable' => FALSE,
            'field cache' => FALSE,
            'static cache' => TRUE,
            'entity cache' => TRUE,
            'entity keys' => array(
                'id' => 'event_id',
                'label' => 'event_name'
            ),
            'controller class' => 'EventController',
            'entity class' => 'EventEntity',
            'label callback' => 'entity_node_label',
            'bundles' => array(
                'show' => array(
                    'label' => t('Show')
                ),
                'performance' => array(
                    'label' => t('Performance')
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
        ),
        'performance' => array(
            'label' => t('Performance'),
            'base table' => 'dcc_entity_performance',
            'fieldable' => FALSE,
            'field cache' => FALSE,
            'static cache' => TRUE,
            'entity cache' => TRUE,
            'entity keys' => array(
                'id' => 'performance_id',
            ),
            'controller class' => 'PerformanceController',
            'entity class' => 'PerformanceEntity',
            'label callback' => 'entity_node_label',
            'access callback' => 'dannyscomedyclub_entity_access',
            'access arguments' => 'performance',
            'uri callback' => 'dcc_entity_node_uri',
            'bundles' => array(
                'performances' => array(
                    'label' => t('Performances')
                )
            ),
            'view modes' => array(
                'full' => array(
                    'label' => t('Full content'),
                    'custom settings' => FALSE,
                ),
                'performances_view' => array(
                    'label' => t('Performances Content')
                )
            ),
            'admin ui' => array(
                'path' => 'admin/performance',
                'menu wildcard' => '%entity_object',
                'file path' => drupal_get_path('module', 'entity'),
                'file' => 'includes/entity.ui.inc'
            )
        ),
        'show' => array(
            'label' => t('Show'),
            'base table' => 'dcc_entity_show',
            'entity keys' => array(
                'id' => 'show_id'
            ),
            'fieldable' => FALSE,
            'field cache' => FALSE,
            'static cache' => TRUE,
            'entity cache' => TRUE,
            'controller class' => 'ShowController',
            'entity class' => 'ShowEntity',
            'label callback' => 'entity_node_label',
            'uri callback' => 'dcc_entity_node_uri',
            'access callback' => 'dannyscomedyclub_entity_access',
            'access arguments' => 'show',
            'bundles' => array(
                'shows' => array(
                    'label' => t('Shows')
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
                'path' => 'admin/show',
                'menu wildcard' => '%entity_object',
                'file path' => drupal_get_path('module', 'entity'),
                'file' => 'includes/entity.ui.inc'
            )
        )
    );
    
    return $event_entity;
}

function event_entity_info_alter(&$entity_info) {
    $entity_info['node']['bundles']['shows']['uri callback'] = 'dannyscomedyclub_uri';
    $entity_info['node']['bundles']['performances']['uri callback'] = 'dannyscomedyclub_uri';
}

?>