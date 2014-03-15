<?php

class EventCRUD {
    static public function event_form(&$form, &$form_state, $entity, $node) {
        $event_status = taxonomy_vocabulary_machine_name_load('event_status');
        
        $form['event'] = array(
            '#type' => 'fieldset',
            '#title' => t('Event Fields'),
            '#collapsible' => TRUE,
            '#collapsed' => TRUE,
            '#weight' => 2
        );

        $form['event']['entity_taxonomy_event_status_id'] = array(
            '#type' => 'select',
            '#title' => t('Status of the Performance'),
            '#default_value' => !is_null($entity->getEventStatus()) ? $entity->getEventStatus() : NULL,
            '#empty_value' => '',
            '#empty_option' => 'None Selected',
            '#required' => TRUE,
            '#options' => !empty($event_status) ? taxonomy_allowed_values(array(
                'settings' => array(
                    'allowed_values' => array(
                        array(
                            'vocabulary' => 'event_status',
                            'parent' => 0
                        )
                    )
                )
            )) : array()
        );
        
        $form['event']['event_date'] = array(
            '#type' => 'date_select',
            '#title' => 'Event Date',
            '#id' => 'event-date-add',
            '#default_value' => !is_null($entity->getDate()) ? $entity->getDate() :'',
            '#description' => t('The Date of the Event')
        );
        
        if($entity->getBundleString() == 'show') {
            $form['event']['event_date']['#required'] = TRUE;
        } else {
            $form['event']['event_date']['#required'] = FALSE;
        }
        
        $form['event']['image_caption'] = array(
            '#type' => 'textfield',
            '#title' => t('Image Caption'),
            '#description' => t('Enter the Caption/Courtesy of the Image'),
            '#default_value' => !is_null($entity->getImageCaption()) ? $entity->getImageCaption() : NULL
        );

        $form['event']['event_url'] = array(
            '#type' => 'textfield',
            '#default_value' => !is_null($entity->getUrl()) ? $entity->getUrl() : NULL,
            '#description' => t('Enter the URL of the Event'),
            '#title' => t('Event URL'),
            '#attributes' => array('type' => 'url')
        );

        $form['event']['event_name'] = array(
            '#type' => 'textfield',
            '#default_value' => !is_null($entity->getName()) ? $entity->getName() : NULL,
            '#description' => t('Enter the Name of the Event'),
            '#title' => t('Event Name')
        );
        
        $form['promo'] = array(
            '#type' => 'fieldset',
            '#title' => t('Promotional Fields'),
            '#collapsible' => TRUE,
            '#collapsed' => TRUE,
            '#weight' => 2
        );
        
        $form['promo']['event_image_file_id'] = array(
            '#type' => 'managed_file',
            '#title' => t('Promotional Image'),
            '#description' => t('Promotional Image for the Event'),
            '#default_value' => !is_null($entity->getEventImage()) ? $entity->getEventImage() : '',
            '#upload_location' => (is_object($node) && property_exists($node, 'type') && $node->type == 'shows') ? 
            'public://promo-image/shows/' : (is_object($node) && property_exists($node, 'type') && $node->type == 'performances') ? 'public://promo-image/performances/' : ''
        );
        
        $event_bundle = '';
        $bool = !empty($form_state['values']['ajax_event_bundle']);
        if(!is_null($entity->getPromoEvent())) {
            $event_bundle = entity_load_single('event', $entity->getPromoEvent())->getBundleString();
        }
        
        $form['promo']['ajax_event_bundle'] = array(
            '#type' => 'select',
            '#title' => t('Event Type'),
            '#description' => t('Select the Event Type'),
            '#options' => entity_get_controller('event')->getEntityBundles(),
            '#empty_value' => '',
            '#empty_option' => 'None Selected',
            '#ajax' => array(
                'callback' => 'event_add_event_bundles',
                'method' => 'html',
                'effect' => 'fade',
                'event' => 'change',
                'wrapper' => 'event-image-event-id-wrapper'
            ),
            '#default_value' => $event_bundle
        );
        
        $form['promo']['event_image_event_id_wrapper'] = array(
            '#type' => 'html_tag',
            '#tag' => 'div',
            '#attributes' => array('id' => 'event-image-event-id-wrapper')
        );
        
        if(!is_null($entity->getPromoEvent()) && !$bool) {
            $form['promo']['event_image_event_id'] = event_add_event_bundles($form, $form_state, $entity->getPromoEvent(), $event_bundle); // set form for loading
        } else {
            $form['promo']['event_image_event_id'] = event_add_event_bundles($form, $form_state, NULL, ''); // initialise the form
        }
    }
    
    static public function event_form_validate($node) {
        $term = taxonomy_term_load($node->entity_taxonomy_event_status_id);
        $vocab = taxonomy_vocabulary_machine_name_load('event_status');
        if(!empty($term) && (empty($term->name) || $term->vid !== $vocab->vid)) {
            form_set_error('entity_taxonomy_event_status_id', 'Select valid Event Status');
        }
        
        if(!empty($node->image_caption) && !drupal_validate_utf8($node->image_caption)) {
            form_set_error('image_caption', 'Enter Valid Image Caption');
        }

        if(!empty($node->event_name) && !drupal_validate_utf8($node->event_name)) {
            form_set_error('event_name', 'Enter Valid Event Name');
        }

        if(!empty($node->event_url) && !preg_match('/\b([\d\w\.\/\+\-\?\:]*)((ht|f)tp(s|)\:\/\/|[\d\d\d|\d\d]\.[\d\d\d|\d\d]\.|www\.|\.tv|\.ac|\.com|\.edu|\.gov|\.int|\.mil|\.net|\.org|\.biz|\.info|\.name|\.pro|\.museum|\.co)([\d\w\.\/\%\+\-\=\&amp;\?\:\\\&quot;\'\,\|\~\;]*)\b/', 
                $node->event_url)) {
            form_set_error('event_url', 'Enter valid Event URL');
        }
        
        $file = file_load($node->event_image_file_id);
        if(!empty($file) && empty($file->uri)) {
            form_set_error('event_image_file_id', t('Select Valid Event Image File'));
        }
        
        if(!empty($node->ajax_event_bundle) && empty($node->event_image_event_id)) {
            form_set_error('event_image_event_id', t('Select Valid Event for the Image'));
        }
    }
}

?>
