<?php 

function md_minimal_select($variables) {
    $javascript = &drupal_static(__FUNCTION__, array());
    $element = $variables['element'];
    element_set_attributes($element, array('id', 'name', 'size'));
    _form_set_class($element, array('form-select'));
    $output = "<select data-dojo-type=\"dijit/form/Select\"".drupal_attributes($element['#attributes']) . ">" . form_select_options($element) . "</select>";
    return MdMinimalCommon::processFieldJs($javascript, $element, $output);
}

function md_minimal_textarea($variables) {
    $javascript = &drupal_static(__FUNCTION__, NULL);
    $element = $variables['element'];
    element_set_attributes($element, array('id', 'name', 'cols', 'rows'));
    _form_set_class($element, array('form-textarea'));
    
    $wrapper_attributes = array(
        'class' => array('form-textarea-wrapper'),
    );
    $output = '<div' . drupal_attributes($wrapper_attributes) . '><select data-dojo-type="dijit/form/Textarea"' . 
            drupal_attributes($element['#attributes']) . '>' . form_select_options($element) . '</select></div>';
    return MdMinimalCommon::processFieldJs($javascript, $element, $output);
}

function md_minimal_text_format_wrapper($variables) {
    $javascript = &drupal_static(__FUNCTION__, NULL);
    $element = $variables['element'];
    $output = '<div class="text-format-wrapper">';
    $output .= $element['#children']; // add the "dijit/Editor" here; data-dojo-type="dijit/Editor" id="editor1"
    if (!empty($element['#description'])) {
    $output .= '<div class="description">' . $element['#description'] . '</div>';
    }
    $output .= "</div>\n";
    return MdMinimalCommon::processFieldJs($javascript, $element, $output);
}

function md_minimal_textfield($variables) {
    $javascript = &drupal_static(__FUNCTION__, NULL);
    $element = $variables['element'];
    $element['#attributes']['type'] = 'text';
    element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength'));
    _form_set_class($element, array('form-text'));

    $extra = '';
    if ($element['#autocomplete_path'] && drupal_valid_path($element['#autocomplete_path'])) {
        drupal_add_library('system', 'drupal.autocomplete');
        $element['#attributes']['class'][] = 'form-autocomplete';

        $attributes = array();
        $attributes['type'] = 'hidden';
        $attributes['id'] = $element['#attributes']['id'] . '-autocomplete';
        $attributes['value'] = url($element['#autocomplete_path'], array('absolute' => TRUE));
        $attributes['disabled'] = 'disabled';
        $attributes['class'][] = 'autocomplete';
        $extra = '<input' . drupal_attributes($attributes) . ' />';
    }

    $output = '<input data-dojo-type="dijit/form/TextBox"
    data-dojo-props="trim:true, propercase:true"' . drupal_attributes($element['#attributes']) . ' />';
    return MdMinimalCommon::processFieldJs($javascript, $element, $output);
}

function md_minimal_checkbox($variables) {
    $javascript = &drupal_static(__FUNCTION__, NULL);
    $element = $variables['element'];
    $t = get_t();
    $element['#attributes']['type'] = 'checkbox';
    element_set_attributes($element, array('id', 'name', '#return_value' => 'value'));

    // Unchecked checkbox has #value of integer 0.
    if (!empty($element['#checked'])) {
        $element['#attributes']['checked'] = 'checked';
    }
    _form_set_class($element, array('form-checkbox'));
    return MdMinimalCommon::processFieldJs($javascript, $element, $output);
}

function md_minimal_checkboxes($variables) {
    $javascript = &drupal_static(__FUNCTION__, NULL);
    $element = $variables['element'];
    $attributes = array();
    if (isset($element['#id'])) {
        $attributes['id'] = $element['#id'];
    }
    $attributes['class'][] = 'form-checkboxes';
    if (!empty($element['#attributes']['class'])) {
        $attributes['class'] = array_merge($attributes['class'], $element['#attributes']['class']);
    }
    if (isset($element['#attributes']['title'])) {
        $attributes['title'] = $element['#attributes']['title'];
    }
    return MdMinimalCommon::processFieldJs($javascript, $element, $output);
}

//class MdMinimalCommon {
//    static public function processFieldJs(&$javascript, $element, $output) {
//        if(empty($javascript[$element['#field_interaction']])) {
//            if(isset($element['#field_type']) && isset($element['#field_interaction'])) {
//                if($element['#field_type'] == 'url') {
//                    $page = drupal_html_class('field__'.$element['#field_file']);
//                } else {
//                    $page = drupal_html_class('field_'.$element['#field_type'].'_'.$page['#field_file']);
//                }
//                $javascript[$element['#field_interaction']] = theme_render_template(base_path().path_to_theme().'/templates/html/dojo/field/'.$page.'.tpl.html', array());
//                return $javascript[$element['#field_interaction']].$output;
//            }
//        }
//        return $output;
//    }
//    
//    static function processPageJs($element) {
//        if($element['#page_type'] == 'url') {
//            $page = drupal_html_class('page__'.$element['#page_file']);
//        } else {
//            $page = drupal_html_class('page_'.$element['#page_type'].'_'.$page['#page_file']);
//        }
//        $javascript = theme_render_template(base_path().path_to_theme().'/templates/html/dojo/page/'.$page.'.tpl.html', array());
//        return $javascript;
//    }
//}

?>