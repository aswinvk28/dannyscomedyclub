<?php

class VenueEntity extends CommonEntity {
    var $venue_id;
    var $venue_address;
    var $venue_location;
    var $venue_telephone;
    var $venue_geo_lat;
    var $venue_geo_long;
    var $venue_url;
    var $entity_document_id;
    var $entity_node_bundle_id;
    private $address;
    private $geo;
    private $bundle_node;
    private $bundle_entity;
    var $node_type = 'venue';
    
    public function getParentEntity() {
        if(empty($this->document)) {
            $this->document = entity_get_controller('document')->readEntity($this->entity_document_id);
            $this->document->file_path = 'venue';
            $this->document->file_type = array('text/html', 'html');
        }
        return $this->document;
    }
    
    public function getDocument() {
        return $this->entity_document_id;
    }
    
    public function getBundle() {
        return $this->entity_node_bundle_id;
    }
    
    public function getBundleNode() {
        if(empty($this->bundle_node) && !is_null($this->getBundle())) {
            $this->bundle_node = node_load($this->getBundle());
        }
        return $this->bundle_node;
    }
    
    public function getBundleTitle() {
        $node = $this->bundle_node;
        if(empty($this->bundle_node)) {
            $entity = $this->getBundleEntity();
            $entity->initialize();
            return (!empty($entity) && !is_null($entity->getTitle())) ? $entity->getTitle() : '';
        }
        return (!empty($node) && property_exists($node, 'title')) ? $node->title : '';
    }
    
    public function getBundleEntity() {
        if(empty($this->bundle_entity)) {
            $this->bundle_entity = new NodeEntity(array(
                'nid' => $this->getBundle(),
                'type' => $this->node_type
            ), 'node');
        }
        return $this->bundle_entity;
    }
    
    public function getAddress() {
        if(empty($this->address)) {
            $this->address = $this->getEntityField(array('venue_address', 'venue_location', 'venue_telephone'));
            if(!empty($this->address)) {
                list($this->venue_address, $this->venue_location, $this->venue_telephone) = array_values((array) $this->address);
            }
        }
        return $this->address;
    }
    
    public function getGeo() {
        if(empty($this->geo)) {
            $this->geo = $this->getEntityField(array('venue_geo_lat', 'venue_geo_long'));
            if(!empty($this->geo)) {
                list($this->venue_geo_lat, $this->venue_geo_long) = array_values((array) $this->geo);
            }
        }
        return $this->geo;
    }
    
    public function getVenueGeoLat() {
        return $this->venue_geo_lat;
    }
    
    public function getVenueGeoLong() {
        return $this->venue_geo_long;
    }
    
    public function getVenueAddress() {
        return $this->venue_address;
    }
    
    public function getVenueLocation() {
        return $this->venue_location;
    }
    
    public function getVenueTelephone() {
        return $this->venue_telephone;
    }
    
    public function getVenueUrl() {
        return $this->venue_url;
    }
}

?>