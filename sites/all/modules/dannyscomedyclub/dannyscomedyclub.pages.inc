<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

function dannyscomedyclub_nodetype_view($node_type, $node) {
    return DannysComedyClubRouteFactory::getRouteInstance()->renderNode($node, $node_type);
}

function dannyscomedyclub_nodetitle($node_type, $node) {
    $uri = dannyscomedyclub_uri($node);
    return node_type_get_name($node) . ': <a class="underline" href="'.url($uri['path'], array('base_url' => TRUE)).'">'.$node->title.'</a>';
}

function dannyscomedyclub_display_page() {
    $args = func_get_args();
    return DannysComedyClubRouteFactory::getRouteInstance()->renderDisplay($args);
}

function dannyscomedyclub_display_content() {
    $vars = array();
    $args = func_get_args();
    $vars['proceed'] = false;
    DannysComedyClubRouteFactory::getRouteInstance()->contentRenderVariables($vars, $args);
    if(isset($vars['query']) && $vars['proceed'] == true) {
        return DannysComedyClubRouteFactory::getRouteInstance()->renderDisplay($vars['query'], $vars);
    } else {
        drupal_not_found();
    }
}

function page_value_load($page, $slug, $number) {
    return (int) $number;
}

function dannyscomedyclub_delivery_html($page_callback_result) {
    if(isset($page_callback_result['#node'])) {
        drupal_deliver_html_page($page_callback_result);
    } else {
        drupal_deliver_html_page(MENU_NOT_FOUND);
    }
}

function dannyscomedyclub_display_front_page() {
    drupal_set_title(t("@site-name"."'s Shows", array('@site-name' => variable_get('site_name', 'Drupal'))), PASS_THROUGH);

    $build['default_message'] = array(
      '#markup' => '',
      '#prefix' => '<div id="first-time">',
      '#suffix' => '</div>',
    );
    return $build;
}

?>