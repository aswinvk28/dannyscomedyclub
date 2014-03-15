<?php

class PerformerCRUD {
    public static function set_node_type($entity, &$node) {
        $entity_id = $entity->getEntityId();
        $bool = is_object($node) && property_exists($node, 'nid');
        if(is_object($node)) {
            $type = node_type_get_type($node);
        }
        if(isset($entity_id)) {
           $entity->getOptions();
            if(!$bool) {
                $node = $entity->getBundleNode();
            }
        }
        return $type;
    }
    
    static public function performer_node_form(&$form, $form_state, $node) {
        $entity = entityfunctionality_set_entity_bundle_node('performer', $node);
        
        $form = self::performer_entity_form($form, $form_state, $entity, $node);
    }
    
    static public function performer_entity_form($form, $form_state, $entity, $node = NULL) {
        $type = self::set_node_type($entity, $node);
        
        $form['title'] = array(
            '#type' => 'textfield',
            '#title' => check_plain($type->title_label),
            '#default_value' => (is_object($node) && property_exists($node, 'title')) ? $node->title : '',
            '#required' => TRUE,
            '#weight' => -5,
        );
        
        $form['performer_options'] = array(
            '#type' => 'fieldset',
            '#title' => t('Performer Properties'),
            '#collapsible' => TRUE,
            '#collapsed' => TRUE,
            '#group' => 'visibility'
        );

        $form['performer_options']['performer_email'] = array(
            '#type' => 'textfield',
            '#title' => t('Performer Email'),
            '#description' => t('Enter the email of the performer'),
            '#default_value' => !is_null($entity->getEmail()) ? $entity->getEmail() : '',
            '#attributes' => array('type' => 'email')
        );

        $form['performer_options']['performer_fb'] = array(
            '#type' => 'textfield',
            '#title' => t('Performer Facebook Page'),
            '#description' => t('Enter the FB Page of the performer'),
            '#default_value' => !is_null($entity->getFB()) ? $entity->getFB() : '',
            '#attributes' => array('type' => 'url')
        );

        $form['performer_options']['performer_twitter'] = array(
            '#type' => 'textfield',
            '#title' => t('Performer Twitter Page'),
            '#description' => t('Enter the Twitter Page of the performer'),
            '#default_value' => !is_null($entity->getTwitter()) ? $entity->getTwitter() : '',
            '#attributes' => array('type' => 'url')
        );

        $form['performer_options']['performer_yt'] = array(
            '#type' => 'textfield',
            '#title' => t('Performer Youtube Page'),
            '#description' => t('Enter the Youtube Link of the performer'),
            '#default_value' => !is_null($entity->getYt()) ? $entity->getYt() : '',
            '#attributes' => array('type' => 'url')
        );

        $form['performer_options']['performer_website'] = array(
            '#type' => 'textfield',
            '#title' => t('Performer Website'),
            '#description' => t('Enter the Website of the performer'),
            '#default_value' => !is_null($entity->getWebsite()) ? $entity->getWebsite() : '',
            '#attributes' => array('type' => 'url')
        );

        return $form;
    }
    
}

?>