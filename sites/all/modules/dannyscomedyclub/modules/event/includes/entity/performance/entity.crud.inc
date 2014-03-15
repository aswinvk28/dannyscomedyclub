<?php 

class PerformanceCRUD {
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
    
    public static function performance_node_form(&$form, $form_state, $node) {
        $entity = entityfunctionality_set_entity_bundle_node('performance', $node);
        
        $form = self::performance_entity_form($form, $form_state, $entity, $node);
    }
    
    public static function performance_entity_form($form, $form_state, $entity, $node = NULL) {
        $type = self::set_node_type($entity, $node);
        
        $form['title'] = array(
            '#type' => 'textfield',
            '#title' => check_plain($type->title_label),
            '#default_value' => (is_object($node) && property_exists($node, 'title')) ? $node->title : '',
            '#required' => TRUE,
            '#weight' => -10,
        );
        
        EventCRUD::event_form($form, $form_state, $entity->getParentEntity(), $node);
        
        $show_options = array();
        $show_nodes = node_load_multiple(array(), array(
            'type' => 'shows'
        ));
        if(!empty($show_nodes)) {
            foreach($show_nodes as $show_entity_id => $show_node) {
                $show_options[$show_entity_id] = $show_node->title;
            }
        }
        $form['entity_node_shows_id'] = array(
            '#type' => 'select',
            '#title' => 'Show',
            '#default_value' => !is_null($entity->getShow()) ? $entity->getShow() : '',
            '#empty_value' => '',
            '#empty_option' => 'None Selected',
            '#options' => $show_options,
            '#required' => TRUE,
            '#description' => t('The Show for the Performance'),
            '#weight' => 0,
        );

        $performer_options = array();
        $entities = entity_load('performer');
        if(!empty($entities)) {
            foreach($entities as $entity_id => $performer_entity) {
                $performer_options[$entity_id] = entity_label('performer', $performer_entity);
            }
        }
        $form['entity_performer_id'] = array(
            '#type' => 'select',
            '#title' => t('Select Performer'),
            '#empty_value' => '',
            '#empty_option' => 'None Selected',
            '#options' => $performer_options,
            '#required' => TRUE,
            '#default_value' => !is_null($entity->getPerformer()) ? $entity->getPerformer() : '',
            '#weight' => 1,
        );

        $form['performance_order'] = array(
            '#type' => 'textfield',
            '#title' => 'Order of Appearance',
            '#default_value' => !is_null($entity->getOrder()) ? $entity->getOrder() : '',
            '#description' => t('The order of display'),
            '#weight' => -2
        );

        $performance_types = taxonomy_vocabulary_machine_name_load('performances_types');
        
        $form['entity_taxonomy_performances_types_id'] = array(
            '#type' => 'select',
            '#title' => t('Performance Type'),
            '#default_value' => !is_null($entity->getPerformanceType()) ? $entity->getPerformanceType() : '',
            '#description' => t('The type of performance'),
            '#empty_value' => '',
            '#empty_option' => 'None Selected',
            '#options' => !empty($performance_types) ? taxonomy_allowed_values(array(
                'settings' => array(
                    'allowed_values' => array(
                        array(
                            'vocabulary' => 'performances_types',
                            'parent' => 0
                        )
                    )
                )
            )) : array(),
            '#weight' => 0
        );

        $form['performance_video'] = array(
            '#type' => 'textfield',
            '#title' => t('Performance Video'),
            '#default_value' => !is_null($entity->getVideo()) ? $entity->getVideo() : '',
            '#description' => t('Enter the Youtube Video url of the performance'),
            '#weight' => 4
        );

        return $form;
    }
}

?>