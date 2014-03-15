<?php

function adjacentsystem_entity_info() {
    return array(
        'adjacentsystem' => array(
            'label' => t('Adjacent System'),
            'field cache' => FALSE,
            'static cache' => TRUE,
            'entity cache' => TRUE,
            'fieldable' => FALSE,
            'bundles' => array(
                'ndreference' => array(
                    'label' => t('Node Document Reference')
                ),
                'pressquotation' => array(
                    'label' => t('Quote')
                )
            ),
        )
    );
}

?>