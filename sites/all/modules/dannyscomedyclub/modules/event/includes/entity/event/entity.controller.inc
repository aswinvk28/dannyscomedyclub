<?php 

class EventController extends EntityCRUD {
    
    protected function buildQuery($ids, $conditions = array()) {
        $query = parent::buildQuery($ids, $conditions);
        $fields = & $query->getFields();
        unset($fields['event_image_file_id']);
        unset($fields['event_image_event_id']);
        unset($fields['image_caption']);
        return $query;
    }
    
    public function getBundleController($bundle) {
        if(in_array($bundle, $this->getEntityBundles())) {
            return entity_get_controller($bundle);
        }
        return NULL;
    }
    
}

?>