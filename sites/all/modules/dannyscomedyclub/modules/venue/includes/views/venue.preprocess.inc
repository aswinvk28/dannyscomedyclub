<?php
function venue_venue__venue__list_view(&$vars) {
    $entity = $vars['elements']['#entity'];
    $uri = entity_uri('venue', $entity);
    $info = $entity->entityInfo();
    $more_link = theme('more_link', array(
        'url' => $uri['path'], 
        'title' => t("Read More")
    ));
    $body = theme('hover_block', array(
        'performer' => FALSE,
        'body' => '<p>'.$entity->getParentEntity()->getDocumentBody().'...</p>'.$more_link,
        'link_title' => 'View the '.$info['label'],
        'uri_path' => url($uri['path'], array('base_url' => TRUE))
    ));
    $vars['venue_fields'] = array(
        'body' => $body
    );
}

function venue_venue__venue__full(&$vars) {
    drupal_add_js(
        'http://maps.googleapis.com/maps/api/js?key=AIzaSyC2shLzP7Hd3ZeYDXU9v7XlG_wJ9hgiPAc&sensor=false&libraries=places', array('group' => JS_LIBRARY, 'every_page' => FALSE, 'scope' => 'footer', 'weight' => -40)
    );
    $entity = $vars['elements']['#entity'];
    $entity->getAddress();
    $entity->getGeo();
    $uri = entity_uri('venue', $entity);
    $vars['url'] = $uri['path'];
    $vars['venue_fields'] = array(
        'address' => $entity->getVenueAddress(),
        'telephone' => $entity->getVenueTelephone(),
        'url' => $entity->getVenueUrl(),
        'body' => $entity->getParentEntity()->getDocumentBody(),
        'map_lat' => !is_null($entity->getVenueGeoLat()) ? $entity->getVenueGeoLat() : '',
        'map_long' => !is_null($entity->getVenueGeoLong()) ? $entity->getVenueGeoLong() : ''
    );
}

?>