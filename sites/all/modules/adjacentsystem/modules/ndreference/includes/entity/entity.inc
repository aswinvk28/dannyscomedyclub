<?php 

class NodeDocumentReferenceEntity extends CommonEntity {
    var $ndreference_id;
    var $entity_document_id;
    var $entity_node_reference_id;
    var $entity_node_bundle_id;
    var $ndreference_name;
    var $entity_taxonomy_agency_id;
    var $ndreference_date;
    var $ndreference_bundle;
    private $document;
    private $reference_entity;
    
    public function getDocument() {
        return $this->entitiy_document_id;
    }
    
    public function getParentEntity() {
        if(empty($this->document)) {
            $entity_document = entity_get_controller('document')->readEntity($this->entity_document_id);
            $this->document = $entity_document;
            $this->document->file_path = 'external';
            $this->document->file_type = array('text/html', 'html');
        }
        return $this->document;
    }
    
    public function getBundleTitle() {
        return $this->getName();
    }
    
    public function getName() {
        return $this->ndreference_name;
    }
    
    public function getAgency() {
        return $this->entity_taxonomy_agency_id;
    }
    
    public function getReference() {
        return $this->entity_node_reference_id;
    }
    
    public function getNodeReferenceEntity() {
        if(empty($this->reference_entity)) {
            $this->reference_entity = new NodeEntity(array(
                'nid' => $this->getReference()
            ), 'node');
            $this->reference_entity->initialize();
        }
        return $this->reference_entity;
    }
    
    public function getBundle() {
        return $this->entity_node_bundle_id;
    }
    
    public function getBundleString() {
        return $this->ndreference_bundle;
    }
    
    public function getDate() {
        return $this->ndreference_date;
    }
    
}

?>