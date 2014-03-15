<?php

function event_field_extra_fields() {
  $extra = array();

  $extra['node']['performances'] = array(
    'form' => array(
      'performer_nid' => array(
          'label' => t('Performer'),
          'description' => t('DannysComedyClub Performance module element'),
          'weight' => -5,
      ),
      'show_nid' => array(
          'label' => t('Show'),
          'description' => t('DannysComedyClub Performance module element'),
          'weight' => -4
      ),
      'image_caption' => array(
          'label' => t('Image Caption'),
          'description' => t('DannysComedyClub Performance module element'),
          'weight' => -2
      ),
      'order_p' => array(
          'label' => t('Order of Display'),
          'description' => t('DannysComedyClub Performance module element'),
          'weight' => 0
      ),
      'performance_type' => array(
          'label' => t('Performance Type'),
          'description' => t('DannysComedyClub Performance module element'),
          'weight' => 1
      ),
      'performance_video' => array(
          'label' => t('Performance Video'),
          'description' => t('DannysComedyClub Performance module element'),
          'weight' => 2
      )
    )
  );
  
  $extra['taxonomy_term']['performances_types'] = array(
      'form' => array(
          'schemaorg_ui_type' => array(
              'label' => t('Schema Type'),
              'description' => t('DannysComedyClub module element'),
              'weight' => -3
          )
      )
  );
  
  $extra['node']['shows'] = array(
    'form' => array(
      'image_caption' => array(
          'label' => t('Image Caption'),
          'description' => t('DannysComedyClub Show module element'),
          'weight' => -4
      )
    )
  );

  return $extra;
}

?>