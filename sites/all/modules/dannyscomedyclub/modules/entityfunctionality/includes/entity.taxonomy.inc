<?php 

interface ReferralTaxonomyEntityCRUDInterface {
    public function readEntitiesFromTaxonomy($nid);
}

class ReferralTaxonomyEntityCRUD extends ReferralEntityCRUD {
    public function readEntitiesFromTaxonomy($bundle = '') {
        return $this->readEntities(implode('_', array('taxonomy', $bundle)).'_');
    }
}

class TaxonomyEntity extends CommonEntity {
    var $tid;
    private $name;
    private $taxonomy;
    
    public function getTaxonomy() {
        if(empty($this->taxonomy)) {
            $this->taxonomy = taxonomy_term_load($this->tid);
        }
        return $this->taxonomy;
    }
    
    public function getName() {
        if(empty($this->name)) {
            $name = $this->getEntityField(array($this->entityInfo['entity keys']['label']));
            list($this->name) = array_values((array) $name);
        }
        return $this->name;
    }
}

?>