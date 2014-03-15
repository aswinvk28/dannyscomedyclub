<?php

class VenueCRUD {
    public static function set_node_type($entity, &$node) {
        $entity_id = $entity->getEntityId();
        $bool = is_object($node) && property_exists($node, 'nid');
        if(is_object($node)) {
            $type = node_type_get_type($node);
        }
        if(isset($entity_id)) {
            $entity->getAddress();
            $entity->getGeo();
            if(!$bool) {
                $node = $entity->getBundleNode();
            }
        }
        return $type;
    }
    
    static public function venue_node_form(&$form, $form_state, $node) {
        $entity = entityfunctionality_set_entity_bundle_node('venue', $node);
        
        $form = self::venue_entity_form($form, $form_state, $entity, $node);
    }
    
    static function venue_entity_form($form, $form_state, $entity, $node = NULL) {
        $type = self::set_node_type($entity, $node);
        
        DocumentCRUD::document_mini_form($form, $entity->getParentEntity());
        
        $form['title'] = array(
            '#type' => 'textfield',
            '#title' => check_plain($type->title_label),
            '#default_value' => $entity->getBundleTitle(),
            '#required' => TRUE,
            '#weight' => -5,
        );
        
        $form['address'] = array(
            '#type' => 'fieldset',
            '#title' => t('Address'),
            '#collapsible' => TRUE,
            '#collapsed' => FALSE,
            '#group' => 'visibility'
        );
        
        $form['address']['venue_address'] = array(
            '#type' => 'textarea',
            '#title' => t('Enter the address'),
            '#description' => t('The address of the venue'),
            '#default_value' => !is_null($entity->getVenueAddress()) ? $entity->getVenueAddress() : '',
        );
        
        $form['address']['venue_location'] = array(
            '#type' => 'textfield',
            '#title' => t('Enter the specific location'),
            '#description' => t('The location of the venue'),
            '#default_value' => !is_null($entity->getVenueLocation()) ? $entity->getVenueLocation() : ''
        );
        
        $form['address']['venue_telephone'] = array(
            '#type' => 'textfield',
            '#title' => t('Enter the phone number'),
            '#description' => t('The contact number of the venue'),
            '#default_value' => !is_null($entity->getVenueTelephone()) ? $entity->getVenueTelephone() : ''
        );
        
        $form['geo'] = array(
            '#type' => 'fieldset',
            '#title' => t('Geographical Coordinates'),
            '#collapsible' => TRUE,
            '#collapsed' => FALSE,
            '#group' => 'visibility'
        );
        
        $form['geo']['venue_geo_lat'] = array(
            '#type' => 'textfield',
            '#title' => t('Enter Geographical Latitude'),
            '#description' => t('Geographical Latitude'),
            '#default_value' => !is_null($entity->getVenueGeoLat()) ? $entity->getVenueGeoLat() : ''
        );
        
        $form['geo']['venue_geo_long'] = array(
            '#type' => 'textfield',
            '#title' => t('Enter Geographical Longitude'),
            '#description' => t('Geographical Longitude'),
            '#default_value' => !is_null($entity->getVenueGeoLong()) ? $entity->getVenueGeoLong() : ''
        );
        
        $form['venue_url'] = array(
            '#type' => 'textfield',
            '#title' => t('Enter the url of the venue'),
            '#description' => t('Website of the venue'),
            '#default_value' => !is_null($entity->venue_url) ? $entity->venue_url : ''
        );
        
        return $form;
    }
    
    public static function venue_show_entity_form(&$form, $form_state, $entity) {
        $venue_options = array();
        $nodes = node_load_multiple(array(), array(
            'type' => 'venue'
        ));
        if(!empty($nodes)) {
            foreach($nodes as $nid => $node) {
                $venue_options[$nid] = $node->title;
            }
        }
        $form['entity_node_venue_id'] = array(
            '#type' => 'select',
            '#title' => t('Venue'),
            '#description' => t('Select Venue Node'),
            '#default_value' => !is_null($entity->getVenue()) ? $entity->getVenue() : '',
            '#options' => $venue_options,
            '#empty_value' => '',
            '#empty_option' => 'None Selected',
            '#required' => TRUE
        );

        $form['#validate'][] = 'venue_shows_node_form_validate';
    }
}

?>