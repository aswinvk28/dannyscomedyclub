<?php 

function ndreference_entity_info() {
    
    $ndreference_entity = array(
        'ndreference' => array(
            'label' => t('Node Document Reference'),
            'controller class' => 'NodeDocumentReferenceController',
            'entity class' => 'NodeDocumentReferenceEntity',
            'base table' => 'dcc_entity_ndreference',
            'field cache' => FALSE,
            'static cache' => TRUE,
            'entity cache' => TRUE,
            'fieldable' => FALSE,
            'label callback' => 'entity_node_label',
            'bundles' => array(
                'review' => array(
                    'label' => t('Review')
                ),
                'press_release' => array(
                    'label' => t('Press Release')
                )
            ),
            'entity keys' => array(
                'id' => 'ndreference_id',
                'label' => 'ndreference_name',
                'bundle' => 'ndreference_bundle'
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
        'review' => array(
            'label' => t('Review'),
            'uri_callback' => 'dcc_numeric_entity_node_uri',
            'controller class' => 'ReviewController',
            'entity class' => 'NodeDocumentReferenceEntity',
            'base table' => 'dcc_entity_ndreference',
            'field cache' => FALSE,
            'static cache' => TRUE,
            'entity cache' => TRUE,
            'access callback' => 'dannyscomedyclub_entity_access',
            'label callback' => 'entity_node_label',
            'bundles' => array(
                'review' => array(
                    'label' => t('Review')
                )
            ),
            'fieldable' => FALSE,
            'entity keys' => array(
                'id' => 'ndreference_id',
                'label' => 'ndreference_name'
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
                'path' => 'admin/review',
                'menu wildcard' => '%entity_object',
                'file path' => drupal_get_path('module', 'entity'),
                'file' => 'includes/entity.ui.inc'
            )
        ),
        'press_release' => array(
            'label' => t('Press Release'),
            'uri_callback' => 'dcc_numeric_entity_node_uri',
            'controller class' => 'PressReleaseController',
            'entity class' => 'NodeDocumentReferenceEntity',
            'base table' => 'dcc_entity_ndreference',
            'field cache' => FALSE,
            'static cache' => TRUE,
            'entity cache' => TRUE,
            'fieldable' => FALSE,
            'access callback' => 'dannyscomedyclub_entity_access',
            'label callback' => 'entity_node_label',
            'bundles' => array(
                'pressrelease' => array(
                    'label' => t('Press Release')
                )
            ),
            'entity keys' => array(
                'id' => 'ndreference_id',
                'label' => 'ndreference_name'
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
                'path' => 'admin/press-release',
                'menu wildcard' => '%entity_object',
                'file path' => drupal_get_path('module', 'entity'),
                'file' => 'includes/entity.ui.inc'
            )
        )
    );
    
    return $ndreference_entity;
    
}

?>