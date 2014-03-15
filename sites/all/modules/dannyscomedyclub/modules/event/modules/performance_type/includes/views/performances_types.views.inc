<?php 

if(class_exists('Entity')):

class PerformanceType extends Entity {
	
    private $type;
    private $term;
    private $performing_type;

    function __construct($term) {
        if(is_object($term)) {
            $this->term = $term;
            $this->id = $term->tid;
            $this->type = taxonomy_term_title($this->term);
        } else {
            $this->id = $term;
        }
    }
    
    function getTerm() {
        if(empty($this->term)) {
            $this->term = taxonomy_term_load($this->id);
            $this->type = taxonomy_term_title($this->term);
        }
        return $this->term;
    }
    
    function getPerformingType() {
        if(empty($this->performing_type)) {
            $performing_type = field_get_items('taxonomy_term', $this->getTerm(), 'field_text_255');
            $this->performing_type = $performing_type[0]['value'];
        }
        return $this->performing_type;
    }

    function getPerformances() {
        if(empty($this->performances)) $this->performances = $this->fetchPerformances();
        return $this->performances;
    }

    function fetchPerformances() {
        $nid_array = taxonomy_select_nodes($this->id, TRUE);
        foreach($nid_array as $nid) {
            $performance = new stdClass();
            $performance->pnid = $nid;
            $performances[$nid] = $performance;
        }
        return $performances;
    }
    
    function viewPerformers() {
        
    }
    
    function viewPerformanceType() {
        $view = taxonomy_term_view($this->getTerm(), 'artistes_performance_types');
        return render($view);
    }

}

endif;

?>