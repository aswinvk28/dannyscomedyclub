<?php 

function ndreference_fields_extra_fields() {
    
    $extra = array();
    
    $extra['node']['reviews'] = array(
        'form' => array(
            'review_author' => array(
                'label' => t('Quoted by Author'),
                'description' => t('External-Club Node Document Reference Module form elements'),
                'weight' => 10
            ),
            'review_agency' => array(
                'label' => t('Quoted by Agency'),
                'description' => t('External-Club Node Document Reference Module form elements'),
                'weight' => 11
            ),
            'review_fid' => array(
                'label' => t('Review File'),
                'description' => t('External-Club Node Document Reference Module form elements'),
                'weight' => 14
            ),
            'review_referer_entity_type' => array(
                'label' => t('Entity Type'),
                'description' => t('External-Club Node Document Reference Module form elements'),
                'weight' => 12
            ),
            'review_referer_entity' => array(
                'label' => t('Entity'),
                'description' => t('External-Club Node Document Reference Module form elements'),
                'weight' => 13
            )
        )
    );
    
    return $extra;
    
}

?>