<?php

class QuoteEntity extends CommonEntity {
    var $quote_id;
    var $entity_taxonomy_author_id;
    var $entity_taxonomy_agency_id;
    var $entity_node_reference_id;
    var $quote;
    var $quote_date;
    private $quote_fetch;
    
    public function getQuote() {
        if(empty($this->quote_fetch)) {
            $this->quote_fetch = $this->getEntityField(array('quote', 'quote_date'));
            if(!empty($this->quote_fetch)) {
                list($this->quote, $this->quote_date) = array_values((array) $this->quote_fetch);
            }
        }
        return $this->quote_fetch;
    }
    
    public function getAuthor() {
        return $this->entity_taxonomy_author_id;
    }
    
    public function getAgency() {
        return $this->entity_taxonomy_agency_id;
    }
    
    public function getReference() {
        return $this->entity_node_reference_id;
    }
    
    public function getQuoteBody() {
        return $this->quote;
    }
    
    public function getDate() {
        return $this->quote_date;
    }
}

?>