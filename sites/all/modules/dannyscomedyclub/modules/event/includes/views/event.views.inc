<?php 

if(class_exists('CoreNodeView')):

class PerformanceNodeView extends CoreNodeView implements CoreNodeViewInterface  {
	
    private $review;
    private $press_release;
    private $review_body;
    private $press_release_body;
    
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

    function getEntity() {
        if(empty($this->entity)) {
            $this->entity = entity_load('performance', FALSE, array(
                'entity_node_bundle_id' => $this->nid
            ));
            $this->entity = current($this->entity);
        }
        return $this->entity;
    }
    
    function setEntity($entity) {
        $this->entity = $entity;
    }
    
    function getPerformanceType() {
        return $this->getEntity()->getPerformanceType();
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
    
    protected function getNDReference($entityType, $show_node_view) {
        $entityTypeField = $entityType;
        if(empty($this->{$entityTypeField})) {
            $this->{$entityTypeField} = $show_node_view->getNDReferenceBody($entityType);
        }
        return $this->{$entityTypeField};
    }
    
    function getTrimmedNDReferenceBody($entityType, $show_node_view) {
        $entityTypeField = $entityType . '_body';
        $this->{$entityTypeField} = $this->getNDReference($entityType, $show_node_view);
        $entityInfo = entity_get_info($entityType);
        if(!empty($this->{$entityTypeField})) {
            foreach($this->{$entityTypeField} as $index => &$body) {
                $data = strip_tags($body, '<blockquote><p><a>');
                $position = (int) strpos($data, entity_label('performer', $this->getEntity()->getPerformerEntity()));
                $body = substr($data, $position, 300).'...'.theme('more_link', array(
                    'url' => key($entityInfo['bundles']) . '/'.$index, 
                    'title' => t("Read More")
                ));
            }
            return $this->{$entityTypeField};
        }
        return '';
    }
    
    function viewVideo($view_mode = 'performances_view') {
        return $this->getEntity()->viewVideo($view_mode);
    }
    
    function viewPhotos() {
        if(!empty($this->getNode()->field_image_multiple)) {
            $field_view = field_view_field('node', $this->node, 'field_image_multiple', 'photos_view');
            return drupal_render($field_view);
        }
        return '';
    }
    
}

class PerformanceFactory {
    private static $instance;

    public static function createPerformance($node) {
        self::$instance = new PerformanceNodeView($node);
        return self::$instance;
    }

    public static function getPerformanceInstance() {
        return self::$instance;
    }
}

class ShowNodeView extends CoreNodeView implements CoreNodeViewInterface {
	
    private $date;
    private $status;
    private $caption;
    private $review;
    private $press_release;
    private $review_body = array();
    private $press_release_body = array();

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

    function getEntity() {
        if(empty($this->entity)) {
            $this->entity = entity_load('show', FALSE, array(
                'entity_node_bundle_id' => $this->nid
            ));
            $this->entity = current($this->entity);
        }
        return $this->entity;
    }
    
    function setEntity($entity) {
        $this->entity = $entity;
    }

    function getTitle() {
        return $this->node->title;
    }
    
    function getCaption() {
        if(empty($this->caption)) {
            $items = field_get_items('node', $this->getNode(), 'field_text_255_two');
            $this->caption = $items[0]['value'];
        }
        return $this->caption;
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

    function getShowDate() {
        $entity = $this->getEntity();
        return $entity->getParentEntity()->getDate();
    }
    
    protected function getNDReference($entityType) {
        $entityTypeField = $entityType;
        if(empty($this->{$entityTypeField})) {
            $this->{$entityTypeField} = entity_get_controller($entityType)->readMultipleEntities(array(), array(
                'entity_node_reference_id' => $this->nid,
                'ndreference_bundle' => $entityType
            ), array(
                'node.status' => 1
            ));
        }
        return $this->{$entityTypeField};
    }
    
    function getNDReferenceBody($entityType) {
        $entityTypeField = $entityType . '_body';
        if(empty($this->{$entityTypeField})) {
            $this->getNDReference($entityType);
            if(!empty($this->{$entityType})) {
                foreach($this->{$entityType} as $id => $review) {
                    $this->{$entityTypeField}[$id] = $review->getParentEntity()->getDocumentBody();
                }
            }
        }
        return $this->{$entityTypeField};
    }
    
    function getTrimmedNDReferenceBody($entityType, $views = null) {
        $output = $this->getNDReferenceBody($entityType);
        $entityInfo = entity_get_info($entityType);
        array_walk($output, function(&$body, $index) use($entityInfo) {
            $body = substr(strip_tags($body, '<blockquote><p><a>'), 0, 700).'...'.theme('more_link', array(
                'url' => key($entityInfo['bundles']) . '/'.$index, 
                'title' => t("Read More")
            ));
        });
        return $output;
    }

    function viewPerformers($view_mode = 'performer_view') {
        $performances = $this->getPerformances();
        if(!empty($performances)) { ?>
    
        <div class="clearfix" id="artistes-masonry">
        <?php 
        $method = 'filter_performers_' . $view_mode . '_' . get_class(current($performances));
        $this->{$method}();
        ?>
        </div>
    
        <?php
        
        }
        
    }
    
    private function filter_performers_performer_view_PerformanceEntity() {
        $performances = $this->getPublishedPerformances();
        $view = '';
        foreach($performances as $performance) {
            $view .= $performance->viewPerformer();
        }
        return $view;
    }
    
    public function filter_performances_front_page_PerformanceEntity() {
        $performance_entities = $this->getPublishedPerformances();
        $view = '';
        if( !empty($performance_entities) ) {
            foreach( $performance_entities as $entity_id => $performance_entity ) :
                $performance = new NodeEntity(array('nid' => $performance_entity->entity_node_performances_id), 'node');
                if($performance->getNode()->promote == '1') {
                    DannysComedyClubDotCom::$promotedPerformances[$performance->getEntityId()] = $performance;
                }
                $node_view = node_view($performance->getNode(), 'front_page');
                $view .= drupal_render($view);
            endforeach;
            $view .= '<div class="clearfix">' . $this->getSummary() . '</div>';
        }
        return $view;
    }

}

class ShowFactory {
	
    private static $instance;

    public static function createShow($node) {
        self::$instance = new ShowNodeView($node);
        return self::$instance;
    }

    public static function getShowInstance() {
        return self::$instance;
    }

}

class ShowEntityView {
    private $entity;
    private $show_status;
    
    public function __construct($entity) {
        $this->entity = $entity;
    }
    
    protected function getShowStatus() {
        if(empty($this->show_status)) {
            $this->show_status = taxonomy_term_load($this->entity->getParentEntity()->getEventStatus())->name;
        }
        return $this->show_status;
    }
    
    function printStatus() {
        $arg = 'title_' . DannysComedyClub::$statusArray[$this->getShowStatus()];
        return $this->{$arg}();
    }
    
    function printClass() {
        $arg = 'show_' . DannysComedyClub::$statusArray[$this->getShowStatus()];
        return $this->{$arg}();
    }

    function show_upcoming() { return 'btn btn-info'; }
    function show_confirmed() { return 'btn btn-warning'; }
    function show_finished() { return 'btn btn-success'; }
    function show_tbc() { return 'btn btn-danger'; }
    function show_closed() { return 'btn btn-success'; }
    function show_cancelled() { return 'btn'; }
    
    function title_upcoming() { return 'upcoming show: line-up confirmed'; }
    function title_confirmed() { return 'line-up confirmed'; }
    function title_finished() { return 'Click to view Details'; }
    function title_tbc() { return 'line-up to be confirmed'; }
    function title_closed() { return 'Click to view Details'; }
    function title_cancelled() { return 'Show is Cancelled'; }
}

endif;

?>