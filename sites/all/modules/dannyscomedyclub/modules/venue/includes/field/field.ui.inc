<?php

function venue_field_extra_fields() {
  $extra = array();

  $extra['node']['shows'] = array(
    'form' => array(
      'venue_nid' => array(
          'label' => t('Venue'),
          'description' => t('DannysComedyClub Venue module element'),
          'weight' => -5,
      )
    )
  );
  
  return $extra;
}

?>