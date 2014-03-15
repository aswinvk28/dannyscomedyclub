<?php

function dcc_shortcode_path_to_theme() {
    return base_path().path_to_theme();
}

function dcc_get_node() {
    $item = menu_get_item();
    return isset($item['map'][1]) ? $item['map'][1] : null;
}

function dcc_get_onclick_js_path($path) {
    return "javascript:window.open('" . $path . "', '_self')";
}

?>