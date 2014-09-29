<?php

class PerformerEntity extends CommonEntity {
    var $entity_node_bundle_id;
    var $performer_email;
    var $performer_fb;
    var $performer_twitter;
    var $performer_yt;
    var $performer_website;
    var $performer_opt;
    var $entity_quote;
    private $options;
    private $bundle_node;
    private $bundle_entity;
    
    public function getBundle() {
        return $this->entity_node_bundle_id;
    }
    
    public function getBundleNode() {
        if(empty($this->bundle_node)) {
            if(!is_null($this->getBundle())) {
                $this->bundle_node = node_load($this->getBundle());
            }
        }
        return $this->bundle_node;
    }
    
    function getPublishedPerformances() {
        if(empty($this->performances)) {
            $this->performances = entity_get_controller('performance')->readMultipleEntities(array(), array(
                'entity_performer_id' => $this->getEntityId()
            ), array(
                'node.status' => 1
            ));
        }
        return $this->performances;
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
            ), 'node');
        }
        return $this->bundle_entity;
    }
    
    public function getOptions() {
        if(empty($this->options)) {
            $this->options = $this->getEntityField(array(
                'performer_email', 'performer_fb', 'performer_twitter', 'performer_yt', 'performer_website', 'performer_opt'
            ));
            if(!empty($this->options)) {
                list($this->performer_email, $this->performer_fb, $this->performer_twitter, $this->performer_yt, $this->performer_website, $this->performer_opt) = 
                array_values((array) $this->options);
            }
        }
        return $this->options;
    }
    
    public function getEmail() {
        return $this->performer_email;
    }
    
    public function getFB() {
        return $this->performer_fb;
    }
    
    public function getTwitter() {
        return $this->performer_twitter;
    }
    
    public function getYt() {
        return $this->performer_yt;
    }
    
    public function getWebsite() {
        return $this->performer_website;
    }
    
    public function getPerformerOptions() {
        return $this->performer_opt;
    }
    
}

?>