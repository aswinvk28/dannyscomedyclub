<?php 

if(class_exists('CoreNodeView')):

class PerformerNodeView extends CoreNodeView implements CoreNodeViewInterface {

    private $review_body;
    private $press_release_body;
    private $performance_types;
    
    function __construct($node) {
        if(is_object($node)) {
            $this->node = $node;
            $this->title = $this->node->title;
            $this->type = $this->node->type;
            $this->nid = $node->nid;
        } else {
            $this->nid = $node;
        }
    }
    
    function getNode() {
        if(empty($this->node)) {
            $this->node = node_load($this->nid);
            $this->title = $this->node->title;
            $this->type = $this->node->type;
        }
        return $this->node;
    }
    
    function setEntity($entity) {
        $this->entity = $entity;
    }
    
    function getEntity() {
        if(empty($this->entity)) {
            $this->entity = entity_load('performer', FALSE, array(
                'entity_node_bundle_id' => $this->nid
            ));
            $this->entity = current($this->entity);
        }
        return $this->entity;
    }
    
    function getSummary() {
        $items = field_get_items('node', $this->getNode(), 'body');
        if(empty($items[0]['summary']) && empty($items[0]['value'])) return '';
        $field = field_view_field('node', $this->getNode(), 'body', array(
        'view_mode' => 'teaser',
        'type' => 'text_summary_or_trimmed',
        'settings'=> array('trim_length' => 200),
        'label' => 'hidden'
        ));
        $uri = dannyscomedyclub_uri($this->getNode());
        return render($field).'...'.theme('more_link', array(
            'url' => $uri['path'], 
            'title' => t("Read More")
        ));
    }
    
    function getTrimmedNDReferenceBody($entityType, $performance_node_views) {
        $output = array();
        $entityTypeField = $entityType . '_body';
        if(empty($this->{$entityTypeField})) {
            foreach($performance_node_views as $performance) {
                $title = entity_label('performer', $performance->getEntity()->getPerformerEntity());
                $show_node_view = new ShowNodeView($performance->getEntity()->getShowEntity()->getBundle());
                $output[$title] = $performance->getTrimmedNDReferenceBody($entityType, $show_node_view);
            }
            $this->{$entityTypeField} = $output;
        }
        return $this->{$entityTypeField};
    }
    
    function getPerformanceTypes() {
        if(empty($this->performance_types)) :
            $performances = $this->getEntity()->getPublishedPerformances();
            $perf_array = array();
            foreach($performances as $performance) {
                $perf_array += $performance->getPerformanceType();
            }
            if(!empty($perf_array)) {
                $query = db_select('taxonomy_term_data', 'ttd')->fields('ttd', array('name'))->distinct()->condition('ttd.tid', $perf_array, 'IN');
                $this->performance_types = $query->execute()->fetchAll('name');
            }
        endif;
        return $this->performance_types;
    }
    
}

class PerformerFactory {
    private static $instance;

    public static function createPerformer($node) {
        self::$instance = new PerformerNodeView($node);
        return self::$instance;
    }

    public static function getPerformerInstance() {
        return self::$instance;
    }
}

endif;

?>