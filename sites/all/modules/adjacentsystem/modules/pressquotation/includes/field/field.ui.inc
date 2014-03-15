<?php

function pressquotation_field_extra_fields_alter(&$info) {
    
    $array = array(
        'form' => array(
            'quote_author' => array(
                'label' => t('Quoted by Author'),
                'description' => t('External-Club Quote Module form elements'),
                'weight' => 10
            ),
            'quote_agency' => array(
                'label' => t('Quoted by Agency'),
                'description' => t('External-Club Quote Module form elements'),
                'weight' => 11
            ),
            'quote_body' => array(
                'label' => t('Quote Body'),
                'description' => t('External-Club Quote Module form elements'),
                'weight' => 14
            ),
            'quote_date' => array(
                'label' => t('Quote Date'),
                'description' => t('')
            )
        )
    );
    
    $info['node']['artistes'] += $array;
    $info['node']['shows'] += $array;
    $info['node']['performances'] += $array;
    
}