<?php 

class ShowCRUD {
    public static function set_node_type($entity, &$node) {
        $entity_id = $entity->getEntityId();
        $bool = is_object($node) && property_exists($node, 'nid');
        if(is_object($node)) {
            $type = node_type_get_type($node);
        }
        if(isset($entity_id)) {
            $entity->getParentEntity()->getImage();
            if(!$bool) {
                $node = $entity->getBundleNode();
            }
        }
        return $type;
    }
    
    public static function show_node_form(&$form, $form_state, $node) {
        $entity = entityfunctionality_set_entity_bundle_node('show', $node);
        
        $form = self::show_entity_form($form, $form_state, $entity, $node);
    }
    
    public static function show_entity_form($form, $form_state, $entity, $node = NULL) {
        $type = self::set_node_type($entity, $node);
        
        $form['title'] = array(
            '#type' => 'textfield',
            '#title' => check_plain($type->title_label),
            '#default_value' => (is_object($node) && property_exists($node, 'title')) ? $node->title : '',
            '#required' => TRUE,
            '#weight' => -5,
        );
        
        EventCRUD::event_form($form, $form_state, $entity->getParentEntity(), $node);
        
        return $form;
    }
}

?>