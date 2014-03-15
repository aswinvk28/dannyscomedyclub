<?php 

function adjacentsystem_fields_extra_fields() {
    
    $extra = $quote_extra_fields = $review_extra_fields = array();
    
    $agency_extra_fields = array(
        'form' => array(
            'author' => array(
                'label' => t('Quoted by Author'),
                'description' => t('DannysComedyClub Adjacent System form elements'),
                'weight' => 10
            ),
            'tid' => array(
                'label' => t('Quoted by Agency'),
                'description' => t('DannysComedyClub Adjacent System form elements'),
                'weight' => 11
            )
        )
    );
    
    foreach($agency_extra_fields['form'] as $key => $field) {
        $quote_extra_fields['form']['quote_' . $key] = $field;
        $review_extra_fields['form']['review_' . $key] = $field;
    }
    
    $quote_extra_fields['form']['quote_body'] = array(
        'label' => t('Quote Body'),
        'description' => t('External-Club Quote Module form elements'),
        'weight' => 14
    );
    
    $review_extra_fields['form']['review_fid'] = array(
        'label' => t('Review File'),
        'description' => t('External-Club Review Module form elements'),
        'weight' => 14
    );
    
    $review_extra_fields['form']['review_referer_entity_type'] = array(
        'label' => t('Entity Type'),
        'description' => t('DannysComedyClub Quote Module form elements'),
        'weight' => 12
    );
    
    $review_extra_fields['form']['review_referer_entity'] = array(
        'label' => t('Entity'),
        'description' => t('DannysComedyClub Quote Module form elements'),
        'weight' => 13
    );
    
    $extra['node']['shows'] = $extra['node']['artistes'] = $extra['node']['performances'] = $quote_extra_fields;
    
    $extra['node']['reviews'] = $review_extra_fields;
    
    return $extra;
    
}

?>