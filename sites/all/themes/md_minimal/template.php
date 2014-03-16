<?php

require_once DRUPAL_ROOT . base_path() . 'sites/default/common/dannyscomedyclub.inc';
require_once DRUPAL_ROOT . base_path() . 'sites/default/common/functions.inc';
require_once DRUPAL_ROOT . base_path() . path_to_theme() . '/utilities.inc';
require_once DRUPAL_ROOT . base_path() . path_to_theme() . '/theme_settings.inc';

class DannysComedyClubRoute {

    public function renderNode($node, $node_type) {
        if ($node->type == $node_type) {
            $view = 'full';
            return node_view($node, $view);
        }
    }

    public function renderDisplay($args, $vars = array()) {
        $file = is_array($args) ? implode('__', $args) : $args;
        return $this->display_content_with_variables($file, $vars);
    }

    public function display_content($file) {
        return theme_render_template(path_to_theme() . '/templates/php/content/content--' . drupal_html_class($file) . '.tpl.php', array());
    }
    
    public function display_content_with_variables($file, $vars) {
        return theme_render_template(path_to_theme() . '/templates/php/content/content--' . drupal_html_class($file) . '.tpl.php', $vars);
    }

    public function htmlRenderVariables(&$vars) {
        $menu_item = menu_get_item();
        $query = str_getcsv($_GET['q'], '/');
        if (isset($vars['page']['content']['system_main']['#node']) || ($menu_item['original_map'][0] == 'node' && !empty($menu_item['map'][1]) && is_object($menu_item['map'][1]))) {
            $node = isset($vars['page']['content']['system_main']['#node']) ? $vars['page']['content']['system_main']['#node'] : $menu_item['map'][1];
            $method = 'html_render_variables_' . $node->type;
            if (method_exists($this, $method)) $this->{$method}($node, $vars);
        } else {
            $query = implode('__', array_map(array($this, 'hyphen_to_underscore'), $query));
            $method = 'html_render_variables__' . $query;
            if (method_exists($this, $method))
                $this->{$method}($vars);
        }
    }

    public function pageRenderVariables(&$vars) {
        $menu_item = menu_get_item();
        
        if (isset($vars['page']['content']['system_main']['#node']) || ($menu_item['original_map'][0] == 'node' && !empty($menu_item['map'][1]) && is_object($menu_item['map'][1]))) {
            $node = isset($vars['page']['content']['system_main']['#node']) ? $vars['page']['content']['system_main']['#node'] : $menu_item['map'][1];
            $method = 'page_render_variables_' . $node->type;
            if (method_exists($this, $method)) $this->{$method}($node, $vars);
        } else {
            $query = str_getcsv($_GET['q'], '/');
            $query = implode('__', array_map(array($this, 'hyphen_to_underscore'), $query));
            $method = 'page_render_variables__' . $query;
            if (method_exists($this, $method))
                $this->{$method}($vars);
        }
    }
    
    public function entityRenderVariables(&$vars) {
        if ($id = entity_id($vars['entity_type'], $vars['elements']['#entity'])) {
            $length = count($vars['theme_hook_suggestions']);
            $hook = $vars['theme_hook_suggestions'][$length - 2];
        } else {
            $hook = array_pop($vars['theme_hook_suggestions']);
        }
        if(method_exists($this, $hook)) {
            $this->{$hook}($vars);
        } elseif(module_hook($vars['entity_type'], $hook)) {
            $function = $vars['entity_type'] . '_' . $hook;
            $function($vars);
        }
    }
    
    /* Only executes one slug at a time and not two slugs like "/shows/archive" */
    public function contentRenderVariables(&$vars, $args) {
        $query = array_shift($args);
        $vars['query'] = $query;
        $key = array_search('page', $args);
        if(!empty($args) && !empty($args[$key+1]) && is_numeric($args[$key+1])) {
            $vars['page_number'] = $args[$key+1];
        }
        $method = 'content_render_variables__' . $query;
        if (method_exists($this, $method)) {
            $this->{$method}($vars);
        }
    }

    public function nodeRenderVariables(&$vars) {
        $method = $vars['theme_hook_suggestions'][0];
        if (method_exists($this, $method)) {
            $this->{$method}($vars);
        }
        $hook = $vars['theme_hook_suggestions'][0] . '__' . $vars['view_mode'];
        if (method_exists($this, $hook)) {
            $this->{$hook}($vars);
        }
        $vars['theme_hook_suggestions'] = array($hook);
    }

    public function taxonomyRenderVariables(&$vars) {
        $method = $vars['theme_hook_suggestions'][0];
        if (method_exists($this, $method)) {
            $this->{$method}($vars);
        }
        $vars['theme_hook_suggestions'] = array($method);
    }

    public function fieldRenderVariables(&$vars) {
        $count = count($vars['theme_hook_suggestions']) - 1;
        $method = $vars['theme_hook_suggestions'][$count];
        $hook = $method . '__' . $vars['element']['#view_mode'];
        if (method_exists($this, $method)) {
            $this->{$method}($vars);
        }
        if (method_exists($this, $hook)) {
            $this->{$hook}($vars);
        }
        $vars['theme_hook_suggestions'] = array($method);
    }

    public function blockRenderVariables($block, &$vars) {
        $info = block_custom_block_get($block->delta);
        $info = $this->hyphen_to_underscore($info['info']);
        $method = 'block__' . $block->region . '__' . $info;
        if (method_exists($this, $method)) {
            $this->{$method}($vars);
        }
        $vars['theme_hook_suggestions'][] = $method;
    }

    public function hyphen_to_underscore($item) {
        return $item ? str_replace('-', '_', $item) : '';
    }
    
    public function html_render_variables_shows($node, &$vars) {
        $date = new DateTime(ShowFactory::getShowInstance()->getShowDate());
        $vars['head_title_array']['title'] = 'Show on ' . $date->format('l, d F Y');
        $vars['head_title_array']['page'] .= ' , ' . node_type_get_name('shows');
        drupal_add_css('sites/default/packages/colorbox/colorbox.css', array('group' => CSS_THEME, 'every_page' => FALSE));
        drupal_add_js('sites/default/packages/colorbox/jquery.colorbox-min.js', array('group' => JS_LIBRARY, 'every_page' => FALSE, 'scope' => 'footer', 'weight' => 5));
    }

    public function html_render_variables_artistes($node, &$vars) {
        $vars['head_title_array']['title'] = $node->title;
        $vars['head_title_array']['page'] .= ' , ' . node_type_get_name('artistes');
//        $vars['head_title_array']['tags'] = ' : ' . ArtisteFactory::getArtisteInstance()->printPerformanceTypesTags();
        drupal_add_css('sites/default/packages/colorbox/colorbox.css', array('group' => CSS_THEME, 'every_page' => FALSE));
        drupal_add_js('sites/default/packages/colorbox/jquery.colorbox-min.js', array('group' => JS_LIBRARY, 'every_page' => FALSE, 'scope' => 'footer', 'weight' => 5));
    }

    public function html_render_variables_performances($node, &$vars) {
        $vars['head_title_array']['title'] = $node->title;
        $vars['head_title_array']['page'] .= ' , ' . node_type_get_name('performances');
        drupal_add_css('sites/default/packages/colorbox/colorbox.css', array('group' => CSS_THEME, 'every_page' => FALSE));
        drupal_add_js('sites/default/packages/colorbox/jquery.colorbox.js', array('group' => JS_LIBRARY, 'every_page' => FALSE, 'scope' => 'footer', 'weight' => 5));
    }

    public function html_render_variables__shows(&$vars) {
        $vars['head_title_array']['page'] = ' , ' . implode(' , ', array('Show Times', 'Shows Progress'));
        drupal_add_js('sites/default/packages/jQuery.jPlayer.2.4.0/jQuery.jPlayer.2.4.0/jquery.jplayer.min.js', array('group' => JS_LIBRARY, 'every_page' => TRUE, 'scope' => 'footer', 'weight' => 3));
        drupal_add_css('sites/default/packages/jQuery.jPlayer.2.4.0/jPlayer.Blue.Monday.2.4.0/blue.monday/jplayer.blue.monday.css', array('group' => CSS_THEME, 'every_page' => TRUE, 'scope' => 'header'));
    }
    
    public function html_render_variables__venue(&$vars) {
        $vars['head_title_array']['title'] = 'Venue';
    }

    public function html_render_variables__about_us(&$vars) {
        $vars['head_title_array']['page'] = ' , ' . 'What we do';
        drupal_add_js('sites/default/packages/jQuery.jPlayer.2.4.0/jQuery.jPlayer.2.4.0/jquery.jplayer.min.js', array('group' => JS_LIBRARY, 'every_page' => TRUE, 'scope' => 'footer', 'weight' => 3));
        drupal_add_css('sites/default/packages/jQuery.jPlayer.2.4.0/jPlayer.Blue.Monday.2.4.0/blue.monday/jplayer.blue.monday.css', array('group' => CSS_THEME, 'every_page' => TRUE, 'scope' => 'header'));
    }
    
    public function content_render_variables__artistes(&$vars) {
        drupal_add_js('sites/default/packages/backbone/underscore-min.js', array('group' => JS_LIBRARY, 'every_page' => FALSE, 'scope' => 'footer', 'weight' => 2));
        drupal_add_js('sites/default/packages/backbone/backbone-min.js', array('group' => JS_LIBRARY, 'every_page' => FALSE, 'scope' => 'footer', 'weight' => 3));
        $request_page = isset($_REQUEST['page']) ? (int) $_REQUEST['page'] : !empty($vars['page_number']) ? $vars['page_number'] : 1;
        if(empty($request_page) || $request_page < 0) return;
        $page = $request_page;
        $vars['length'] = 24;
        $count = (int) DannysComedyClubDotCom::getArtistesCount();
        $proceed = ($count % $vars['length'] == 0 && $count / $vars['length'] >= $page) ? true : (($count % $vars['length'] != 0 && (int) ($count / $vars['length']) >= $page - 1) ? true : false);
        if($proceed) {
            $vars['result'] = entity_get_controller('performer')->readMultipleEntities(array(), array(), array(
                'node.status' => 1,
                'performer.range' => array('start' => 0 + ($page - 1) * $vars['length'], 'length' => $vars['length'])
            ));
            $paginator_vars = array(
                'page' => $page,
                'count' => $count,
                'length' => $vars['length']
            );
            $paginator = new DannysComedyClubPaginator($paginator_vars);
            $paginator->render_variables();
            $vars['paginator'] = theme_render_template(path_to_theme() . '/layouts/paginator.php', $paginator->getVars());
            $vars['proceed'] = true;
        }
    }
    
    public function page_render_variables_shows($node, &$vars) {
        $menu_item = menu_get_item();
        if($menu_item['original_map'][0] != 'node' && $menu_item['title_callback'] != 't'):
        $title = $menu_item['title_callback']($menu_item['original_map'][0], $node);
        drupal_set_title($title);
        $vars['title'] = $title;
        endif;
    }

    public function page_render_variables_artistes($node, &$vars) {
        $menu_item = menu_get_item();
        if($menu_item['original_map'][0] != 'node'):
        $title = $menu_item['title_callback']($menu_item['original_map'][0], $node);
        drupal_set_title($title);
        $vars['title'] = $title;
        endif;
    }

    public function page_render_variables_performances($node, &$vars) {
        $menu_item = menu_get_item();
        if($menu_item['original_map'][0] != 'node'):
        $title = $menu_item['title_callback']($menu_item['original_map'][0], $node);
        drupal_set_title($title);
        $vars['title'] = $title;
        endif;
    }
    
    public function pressquotation__pressquotation__general_view(&$vars) {
        $entity = $vars['elements']['#entity'];
        $entity->getQuote();
        $vars['quote_body'] = $entity->getQuoteBody();
        $taxonomy_entity = new TaxonomyEntity(array('tid' => $entity->getAuthor()), 'taxonomy_term');
        $vars['author'] = $taxonomy_entity->getName();
        $taxonomy_entity = new TaxonomyEntity(array('tid' => $entity->getAgency()), 'taxonomy_term');
        $vars['agency'] = $taxonomy_entity->getName();
    }
    
    public function node__shows__full(&$vars) {
        $nid = $vars['node']->nid;
        dannyscomedyclub_memory_queue()->createItem(ShowFactory::createShow($vars['node']));
        $show_node = ShowFactory::getShowInstance();
        $show_entity = entity_load('show', FALSE, array(
            'entity_node_bundle_id' => $nid
        ));
        $show_node->setEntity(current($show_entity));
        $vars['show'] = array();
        $vars['show']['date'] = $show_node->getEntity()->getParentEntity()->getDate();
        
        $show_images_view = field_view_field('node', $show_node, 'field_image_multiple');
        $vars['show']['highlights'] = render($show_images_view);
        
        $vars['venue'] = array();
        $vars['venue']['title'] = entity_label('venue', $show_node->getEntity()->getVenueEntity());
        $uri = entity_uri('show', $show_node->getEntity()->getVenueEntity());
        $vars['venue']['path'] = url($uri['path'], array('base_url' => TRUE));
        
        $vars['show']['performers'] = $vars['show']['performances'] = '';
        $performances = $show_node->getEntity()->getPublishedPerformances();
        if(!empty($performances)) {
            foreach($performances as $entity_id => $performance) {
                $uri = entity_uri('performer', $performances[$entity_id]->getPerformerEntity());
                $vars['show']['performers'] .= theme('performer_view', array(
                    'class' => 'span2 thumbnail',
                    'performer_title' => entity_label('performer', $performances[$entity_id]->getPerformerEntity()),
                    'performer_path' => url($uri['path'], array('base_url' => TRUE)),
                    'performer_image' => field_view_field('node', $performances[$entity_id]->getPerformerEntity()->getBundleNode(), 'field_image', 'scaled_down')
                ));
                $performance_uri = entity_uri('performance', $performance);
                $vars['show']['performances'] .= theme('list_item_view', array(
                    'ul_class' => 'thumbnails',
                    'li_class' => 'thumbnail padding-box label-info pull-left',
                    'items' => array(
                        array(
                            'content' => '<a class="white underline" href="'.url($performance_uri['path'], array('base_url' => TRUE)).'">'.entity_label('performance', $performance).'</a>'
                        )
                    )
                ));
            }
            
            $appeared_performances = array_filter($performances, function($entity) {
                $taxonomy_entity = new TaxonomyEntity(array(
                    'tid' => $entity->getParentEntity()->getEventStatus()
                ), 'taxonomy_term');
                return $taxonomy_entity->getName() == 'Finished';
            });
            
            if(module_exists('ndreference')) {
                $blocks = _block_load_blocks();
                $show_press_releases = $blocks['sidebar']['ndreference_press_release'];
                if(!empty($show_press_releases)) {
                    $block_vars = array();
                    DannysComedyClubRouteFactory::getRouteInstance()->block__sidebar__press_release($block_vars);
                    $vars['press_releases'] = theme_render_template(path_to_theme().'/templates/php/block/block--sidebar--review.tpl.php', $block_vars);
                }
            }

            $vars['show']['photos'] = '';
            if(!empty($appeared_performances)) {
                foreach($appeared_performances as $performance_entity) {
                    $performance_node_entity = new PerformanceNodeView($performance_entity->getBundleNode());
                    $vars['show']['photos'] .= $performance_node_entity->viewPhotos();
                }
                if(module_exists('ndreference')) {
                    $show_reviews = $blocks['sidebar']['ndreference_review'];
                    if(!empty($show_reviews)) {
                        $block_vars = array();
                        DannysComedyClubRouteFactory::getRouteInstance()->block__sidebar__review($block_vars);
                        $vars['reviews'] = theme_render_template(path_to_theme().'/templates/php/block/block--sidebar--review.tpl.php', $block_vars);
                        unset($block_vars);
                    }
                }
            }
        }
        
        $date_interval = DannysComedyClubDotCom::getCurrentAndNextYear();
        $context_shows = entity_get_controller('show')->readMultipleEntities(array(), array(), array(
            'node.status' => 1,
            'event_date' => array(
                'after' => $date_interval['after'],
                'before' => $date_interval['before']
            )
        ));
        if(!empty($context_shows)) {
            $upcoming_shows = array_filter($context_shows, function($entity) {
                $taxonomy_entity = new TaxonomyEntity(array(
                    'tid' => $entity->getParentEntity()->getEventStatus()
                ), 'taxonomy_term');
                return $taxonomy_entity->getName() == 'Upcoming';
            });
            $rest_shows = array_diff_key($context_shows, $upcoming_shows);
            $upcoming_shows = array_map(function($entity) {
                $uri = entity_uri('show', $entity);
                return array(
                    'content' => '<a href="'.url($uri['path'], array('base_url' => TRUE)).'" class="read-more">'.entity_label('show', $entity).'</a>'
                );
            }, $upcoming_shows);
            $vars['show']['upcoming'] = theme('list_item_view', array(
                'ul_class' => 'thumbnails',
                'li_class' => 'thumbnail padding-box label-info pull-left',
                'items' => $upcoming_shows
            ));
            if(!empty($rest_shows)) {
                $finished_shows = array_filter($rest_shows, function($entity) {
                    $taxonomy_entity = new TaxonomyEntity(array(
                        'tid' => $entity->getParentEntity()->getEventStatus()
                    ), 'taxonomy_term');
                    return $taxonomy_entity->getName() == 'Finished';
                });
                $rest_shows = array_diff_key($rest_shows, $finished_shows);
                if(!empty($finished_shows)) {
                    $recent_show = array_shift($finished_shows);
                    $recent_show->getParentEntity()->getImage();
                    $recent_show->getParentEntity()->setBundleEntity($recent_show);
                    if(!is_null($recent_show->getParentEntity()->getEventImage())) {
                        $file = file_load($recent_show->getParentEntity()->getEventImage());
                        if(!empty($file)) {
                            $vars['show']['promo'] = theme('promo_image', array(
                                'event_image_src' => str_replace('public:/', DRUPAL_ROOT.base_path().variable_get('file_public_path', 'sites/default/files'), $file->uri),
                                'event_title' => entity_label('event', $recent_show->getParentEntity())
                            ));
                        }
                    }
                    array_unshift($finished_shows, $recent_show);
                    $finished_shows = array_map(function($entity) {
                        $uri = entity_uri('show', $entity);
                        return array(
                            'content' => '<a href="'.url($uri['path'], array('base_url' => TRUE)).'" class="read-more">'.entity_label('show', $entity).'</a>'
                        );
                    }, $finished_shows);
                    $vars['show']['finished'] = theme('list_item_view', array(
                        'ul_class' => 'thumbnails',
                        'li_class' => 'thumbnail padding-box label-success pull-left',
                        'items' => $finished_shows
                    ));
                }
                if(!empty($rest_shows)) {
                    $rest_shows = array_map(function($entity) {
                        $uri = entity_uri('show', $entity);
                        return array(
                            'content' => '<a href="'.url($uri['path'], array('base_url' => TRUE)).'" class="read-more">'.entity_label('show', $entity).'</a>'
                        );
                    }, $rest_shows);
                    $vars['show']['future'] = theme('list_item_view', array(
                        'ul_class' => 'thumbnails',
                        'li_class' => 'thumbnail padding-box label-warning pull-left',
                        'items' => $rest_shows
                    ));
                }
            }
        }
    }
    
    public function node__artistes__full(&$vars) {
        $nid = $vars['node']->nid;
        dannyscomedyclub_memory_queue()->createItem(PerformerFactory::createPerformer($vars['node']));
        $performer_node = $vars['performer_node'] = PerformerFactory::getPerformerInstance();
        $performer_entity = entity_load('performer', FALSE, array(
            'entity_node_bundle_id' => $nid
        ));
        $performer_node->setEntity(current($performer_entity));
        
        $vars['performer']['title'] = $vars['node']->title;
        $performer_uri = entity_uri('performer', $performer_node->getEntity());
        $vars['performer']['path'] = url($performer_uri['path'], array('base_url' => TRUE));
        $performer_node->getEntity()->getOptions();
        $vars['performer']['website'] = $performer_node->getEntity()->getWebsite();
        
        if(module_exists('performance_type')) {
            if(module_hook('performance_type', __FUNCTION__)) {
                module_invoke('performance_type', __FUNCTION__, $vars);
            }
        }
        
        $performance_entities = $performer_node->getEntity()->getPublishedPerformances();
        if(!empty($performance_entities)) {
            $appeared_performances = array_filter($performance_entities, function($entity) {
                $taxonomy_entity = new TaxonomyEntity(array(
                    'tid' => $entity->getParentEntity()->getEventStatus()
                ), 'taxonomy_term');
                return $taxonomy_entity->getName() == 'Finished';
            });
            $booked_performances = array_diff_key($performance_entities, $appeared_performances);
            
            $appeared_shows = array();
            if(!empty($appeared_performances)) {
                foreach($appeared_performances as $appeared_performance_id => $appeared_performance) {
                    $appeared_show = $appeared_performances[$appeared_performance_id]->getShowEntity();
                    array_push($appeared_shows, $appeared_show);
                }
                
                if(!empty($appeared_shows)) {
                    uasort($appeared_shows, function($show1, $show2) {
                        return ($show1->getParentEntity()->getDate() > $show2->getParentEntity()->getDate()) ? -1 : 1;
                    });
                    $co_performances = array();
                    foreach($appeared_shows as $appeared_show_entity) {
                        $co_performances += $appeared_show_entity->getPublishedPerformances();
                    }
                    $co_performances = array_diff_key($co_performances, $appeared_performances);
                    
                    $vars['co_performers'] = $vars['show_promo'] = '';
                    $vars['photos'] = '';
                    
                    foreach($co_performances as $co_performance) {
                        $uri = entity_uri('performer', $co_performance->getPerformerEntity());
                        $vars['co_performers'] .= theme('performer_view', array(
                            'class' => 'span2 thumbnail',
                            'performer_title' => entity_label('performer', $co_performance->getPerformerEntity()),
                            'performer_path' => url($uri['path'], array('base_url' => TRUE)),
                            'performer_image' => field_view_field('node', $co_performance->getPerformerEntity()->getBundleNode(), 'field_image', 'scaled_down')
                        ));
                    }
                    
                    $performance_node_views = array();
                    foreach($appeared_performances as $performance_entity) {
                        $performance_node_view = new PerformanceNodeView($performance_entity->getBundleNode());
                        $performance_node_view->setEntity($performance_entity);
                        $vars['photos'] .= $performance_node_view->viewPhotos();
                        $performance_node_views[] = $performance_node_view;
                    }
                    $vars['appeared_performances'] = $appeared_performances;
                    
                    if(module_exists('ndreference')) {
                        $blocks = _block_load_blocks();
                        $show_reviews = $blocks['sidebar']['ndreference_review'];
                        if(!empty($show_reviews)) {
                            $block_vars = array('node_views' => $performance_node_views);
                            DannysComedyClubRouteFactory::getRouteInstance()->block__sidebar__review($block_vars);
                            $vars['reviews'] = theme_render_template(path_to_theme().'/templates/php/block/block--sidebar--review.tpl.php', $block_vars);
                        }
                        
                        $show_press_releases = $blocks['sidebar']['ndreference_press_release'];
                        if(!empty($show_press_releases)) {
                            $block_vars = array('node_views' => $performance_node_views);
                            DannysComedyClubRouteFactory::getRouteInstance()->block__sidebar__press_release($block_vars);
                            $vars['press_releases'] = theme_render_template(path_to_theme().'/templates/php/block/block--sidebar--review.tpl.php', $block_vars);
                        }
                    }
                    
                    $recent_performance = array_shift($appeared_performances);
                    $recent_performance->getParentEntity()->getImage();
                    $recent_performance->getParentEntity()->setBundleEntity($recent_performance);
                    if(!is_null($recent_performance->getParentEntity()->getEventImage())) {
                        $file = file_load($recent_performance->getParentEntity()->getEventImage());
                        if(!empty($file)) {
                            $vars['show_promo'] = theme('promo_image', array(
                                'event_image_src' => str_replace('public:/', DRUPAL_ROOT.base_path().variable_get('file_public_path', 'sites/default/files'), $file->uri),
                                'event_title' => entity_label('event', $recent_performance->getParentEntity())
                            ));
                        }
                    }
                }
            }
            
            if(!empty($booked_performances)) {
                uasort($booked_performances, function($performance1, $performance2) {
                    return ($performance1->getShowEntity()->getParentEntity()->getDate() > $performance2->getShowEntity()->getParentEntity()->getDate()) ? -1 : 1;
                });
                $vars['booked_performances'] = $booked_performances;
            }
        }
        
        $performer_press_quotes = entity_load('pressquotation', FALSE, array(
            'entity_node_reference_id' => $nid
        ));
        
        $performer_image = field_view_field('node', $vars['node'], 'field_image');
        $vars['performer_image'] = render($performer_image);
        
        $performer_extra_images = field_view_field('node', $vars['node'], 'field_image_multiple', array('label' => 'hidden'));
        $vars['performer_extra_images'] = render($performer_extra_images);
        
        $vars['performer_press_quotes'] = !empty($performer_press_quotes) ? entity_view('pressquotation', $performer_press_quotes, 'general_view') : '';
    }
    
    public function node__performances__full(&$vars) {
        $nid = $vars['node']->nid;
        dannyscomedyclub_memory_queue()->createItem(PerformanceFactory::createPerformance($vars['node']));
        $performance_node = PerformanceFactory::getPerformanceInstance();
        $performance_entity = entity_load('performance', FALSE, array(
            'entity_node_bundle_id' => $nid
        ));
        $performance_node->setEntity(current($performance_entity));
        
        $performer_entity = $performance_node->getEntity()->getPerformerEntity();
        $vars['performer'] = array();
        $vars['performer']['title'] = entity_label('performer', $performer_entity);
        $uri = entity_uri('performer', $performer_entity);
        $vars['performer']['path'] = url($uri['path'], array('base_url' => TRUE));
        
        $show_entity = $performance_node->getEntity()->getShowEntity();
        $vars['show'] = array();
        $vars['show']['title'] = entity_label('show', $show_entity);
        $uri = entity_uri('show', $show_entity);
        $vars['show']['path'] = url($uri['path'], array('base_url' => TRUE));
        
        $types = require DRUPAL_ROOT.base_path().drupal_get_path('module', 'dannyscomedyclub').'/config/performances_types.inc';
        $taxonomy_entity = new TaxonomyEntity(array(
            'tid' => $performance_node->getEntity()->getPerformanceType()
        ), 'taxonomy_term');
        $vars['itemType'] = $types[$taxonomy_entity->getName()];
        
        $performance_date = new DateTime($show_entity->getParentEntity()->getDate());
        $vars['performance_date'] = $performance_date->format('l\, jS F Y');
        
        $vars['venue'] = array();
        $vars['venue']['title'] = entity_label('venue', $performance_node->getEntity()->getShowEntity()->getVenueEntity());
        $uri = entity_uri('venue', $performance_node->getEntity()->getShowEntity()->getVenueEntity());
        $vars['venue']['path'] = url($uri['path'], array('base_url' => TRUE));
        
        $performance_node->getEntity()->getParentEntity()->getImage();
        $performance_node->getEntity()->getParentEntity()->setBundleEntity(current($performance_entity));
        if(!is_null($performance_node->getEntity()->getParentEntity()->getEventImage())) {
            $file = file_load($performance_node->getEntity()->getParentEntity()->getEventImage());
            if(!empty($file)) {
                $vars['performance_promo'] = theme('promo_image', array(
                    'event_image_src' => str_replace('public:/', DRUPAL_ROOT.base_path().variable_get('file_public_path', 'sites/default/files'), $file->uri),
                    'event_title' => entity_label('event', $performance_node->getEntity()->getParentEntity())
                ));
            }
        }
        
        if(!is_null($performance_node->getEntity()->getVideo())) {
            $performance_video = $performance_node->getEntity()->view('video_view');
            if(!empty($performance_video)) {
                $vars['performance_video'] = drupal_render($performance_video);
            }
        }
        
        if(module_exists('pressquotation')) {
            $performance_quotes = entity_load('pressquotation', FALSE, array(
                'entity_node_reference_id' => $nid
            ));
            $vars['performance_quotes'] = '';
            if(!empty($performance_quotes)) {
                $quote_view = entity_view('pressquotation', $performance_quotes, 'general_view');
                $vars['performance_quotes'] = render($quote_view);
            }
        }
        if(module_exists('ndreference')) {
            $blocks = _block_load_blocks();
            $show_reviews = $blocks['sidebar']['ndreference_review'];
            $show_node_view = new ShowNodeView($performance_node->getEntity()->getShowEntity()->getBundle());
            if(!empty($show_reviews)) {
                $block_vars = array('node_views' => $show_node_view);
                DannysComedyClubRouteFactory::getRouteInstance()->block__sidebar__review($block_vars);
                $vars['reviews'] = theme_render_template(path_to_theme().'/templates/php/block/block--sidebar--review.tpl.php', $block_vars);
            }
            
            $show_press_releases = $blocks['sidebar']['ndreference_press_release'];
            if(!empty($show_press_releases)) {
                $block_vars = array('node_views' => $show_node_view);
                DannysComedyClubRouteFactory::getRouteInstance()->block__sidebar__press_release($block_vars);
                $vars['press_releases'] = theme_render_template(path_to_theme().'/templates/php/block/block--sidebar--review.tpl.php', $block_vars);
            }
        }
        
        $vars['photos'] = $performance_node->viewPhotos();
        
        $vars['co_performers'] = $vars['co_performances'] = '';
        $performances = $show_entity->getPublishedPerformances();
        $performances = array_diff_key($performances, $performance_entity);
        if(!empty($performances)) {
            foreach($performances as $entity_id => $performance) {
                $performer_uri = entity_uri('performer', $performances[$entity_id]->getPerformerEntity());
                $vars['co_performers'] .= theme('performer_view', array(
                    'class' => 'span2 thumbnail',
                    'performer_title' => entity_label('performer', $performances[$entity_id]->getPerformerEntity()),
                    'performer_path' => url($performer_uri['path'], array('base_url' => TRUE)),
                    'performer_image' => field_view_field('node', $performances[$entity_id]->getPerformerEntity()->getBundleNode(), 'field_image', 'scaled_down')
                ));
                $performance_uri = entity_uri('performance', $performance);
                $vars['co_performances'] .= theme('list_item_view', array(
                    'ul_class' => 'thumbnails',
                    'li_class' => 'thumbnail padding-box label-info pull-left',
                    'items' => array(
                        array(
                            'content' => '<a class="underline" href="'.url($performance_uri['path'], array('base_url' => TRUE)).'">'.entity_label('performance', $performance).'</a>'
                        )
                    )
                ));
            }
        }
    }
    
    public function block__sidebar__follow_us(&$vars) {
        $vars['top_block_content'] = theme_get_setting("follow_us");
    }
    
    public function block__sidebar__latest_performers(&$vars) {
        $vars['top_block_content'] = theme_render_template(path_to_theme() . '/layouts/performer-list-performer-view-sidebar.php', array('result' => entity_get_controller('performer')->readMultipleEntities(array(), array(), 
        array(
            'node.status' => 1,
            'performer.range' => array(
                'start' => 0,
                'length' => 20
            )
        ))));
    }
    
    public function block__sidebar__appearing_shows(&$vars) {
        $vars['bottom_block_content'] = theme_render_template(path_to_theme() . '/templates/php/resources/meridian-fm-interview.tpl.php', array());
    }
    
    public function block__sidebar__review(&$vars) {
        $active_instance = DannysComedyClubDotCom::getActiveInstance();
        $node_views = !empty($vars['node_views']) ? $vars['node_views'] : NULL;
        $vars['entityType'] = 'review';
        $vars['review'] = $active_instance->getTrimmedNDReferenceBody($vars['entityType'], $node_views);
    }
    
    public function block__sidebar__press_release(&$vars) {
        $active_instance = DannysComedyClubDotCom::getActiveInstance();
        $node_views = !empty($vars['node_views']) ? $vars['node_views'] : NULL;
        $vars['entityType'] = 'press_release';
        $vars['review'] = $active_instance->getTrimmedNDReferenceBody($vars['entityType'], $node_views);
    }
    
    public function block__sidebar__the_venue(&$vars) {
        $vars['top_block_content'] = theme_render_template(path_to_theme() . '/templates/php/content/content--show-info.tpl.php', array());
    }

    public function field__field_image_multiple__performances(&$vars) {
        $vars['classes_array'][] = 'span3';
        $nid = $vars['element']['#object']->nid;
        $performance_entities = DannysComedyClubDotCom::getActiveInstance()->getEntity()->getPublishedPerformances();
        if(!empty($performance_entities)) {
            $performance_entity = array_filter($performance_entities, function($entity) use ($nid) {
                return $entity->getBundle() == $nid;
            });
            $performance_entity = current($performance_entity);
        } else {
            $performance_entity = PerformanceFactory::getPerformanceInstance()->getEntity();
        }
        $types = require DRUPAL_ROOT.base_path().drupal_get_path('module', 'dannyscomedyclub').'/config/performances_types.inc';
        $taxonomy_entity = new TaxonomyEntity(array(
            'tid' => $performance_entity->getPerformanceType()
        ), 'taxonomy_term');
        $itemType = $types[$taxonomy_entity->getName()];
        
        if(DannysComedyClubDotCom::getActiveInstance() instanceof Show) {
            DannysComedyClubDotCom::getActiveInstance()->getEntity()->getParentEntity()->getImage();
            $vars['image_caption'] = DannysComedyClubDotCom::getActiveInstance()->getEntity()->getParentEntity()->getImageCaption();
            $show_entity = DannysComedyClubDotCom::getActiveInstance()->getEntity();
        } else {
            $performance_entity->getShowEntity()->getParentEntity()->getImage();
            $vars['image_caption'] = $performance_entity->getShowEntity()->getParentEntity()->getImageCaption();
            $show_entity = $performance_entity->getShowEntity();
        }
        
        $uri = entity_uri('show', $show_entity);
        $performance_uri = dcc_entity_node_uri($performance_entity);
        $vars['photos_title'] = theme('photos_title', 
            array(
                'performance_title_attributes' => array(
                    'itemprop' => 'name'
                ),
                'show_title_attributes' => array(
                    'itemprop' => 'name'
                ),
                'itemType' => $itemType,
                'performance_path' => url($performance_uri['path'], array('base_path' => TRUE)),
                'show_path'  => url($uri['path'], array('base_path' => TRUE)),
                'performance_title' => entity_label('performance', $performance_entity),
                'show_title' => entity_label('show', $show_entity)
            )
        );
    }
    
    public function field__field_image_multiple__artistes(&$vars) {
        $vars['classes_array'][] = 'span6';
    }

    public function taxonomy_term__performances_types(&$vars) {
        $term_mapping = $vars['term']->rdf_mapping;
        $vars['attributes_array']['typeof'] = implode(' ', $term_mapping['rdftype']);
        $vars['title_attributes_array']['property'] = implode(' ', $term_mapping['name']['predicates']);
    }
}

class DannysComedyClubRouteFactory {

    private static $instance;

    public static function getRouteInstance() {
        if (empty(self::$instance))
            self::$instance = new DannysComedyClubRoute();
        return self::$instance;
    }

}

/*
 * Here we override the default HTML output of drupal.
 * refer to http://drupal.org/node/550722
 */

// Auto-rebuild the theme registry during theme development.
if (theme_get_setting('clear_registry')) {
    // Rebuild .info data.
    system_rebuild_theme_data();
    // Rebuild theme registry.
    drupal_theme_rebuild();
}

function md_minimal_preprocess_html(&$vars, $hook) {
    if(!$vars['is_admin']) {
        drupal_static_reset('drupal_add_css');
    }
    
    drupal_add_css('sites/default/packages/bootstrap/css/bootstrap.min.css', array('every_page' => TRUE, 'type' => 'file', 'scope' => 'header', 'weight' => -16));
    drupal_add_css('sites/default/packages/bootstrap/css/bootstrap-responsive.min.css', array('every_page' => TRUE, 'type' => 'file', 'scope' => 'header', 'weight' => -15));
    drupal_add_css(path_to_theme() . '/css/style.min.css', array('every_page' => TRUE, 'type' => 'file', 'scope' => 'header', 'weight' => -14));
    drupal_add_js('sites/default/packages/jquery/jquery-1.8.2.min.js', array('group' => JS_LIBRARY, 'every_page' => TRUE, 'weight' => -30, 'scope' => 'footer'));
    
    if(!$vars['is_admin']) {
        $js = &drupal_static('drupal_add_js');
        if(!empty($js)):
        if(array_key_exists('misc/jquery.js', $js) && array_key_exists('misc/ui/jquery.ui.core.min.js', $js)):
        $js['misc/jquery.js'] = $js['misc/ui/jquery.ui.core.min.js'] = array(

        );
        endif;
        endif;
    }
    drupal_add_js(path_to_theme() . '/js/script.js', array('group' => JS_THEME, 'every_page' => TRUE, 'scope' => 'footer', 'weight' => 30));

    $vars['md_minimal_analytics'] = theme_get_setting('md_minimal_analytics');
    $vars['md_minimal_css'] = theme_get_setting('md_minimal_css');
    $vars['classes_array'][] = 'body-patternbg';
    $vars['classes_array'][] = 'claro';
    
    $vars['head_title_array']['tags'] = $vars['head_title_array']['page'] = '';

    if (drupal_is_front_page()) {
        $vars['head_title_array']['title'] = 'Haywards Heath, United Kingdom';
        drupal_add_js('sites/default/packages/jQuery.jPlayer.2.4.0/jQuery.jPlayer.2.4.0/jquery.jplayer.min.js', array('group' => JS_LIBRARY, 'every_page' => TRUE, 'scope' => 'footer', 'weight' => 3));
        drupal_add_css('sites/default/packages/jQuery.jPlayer.2.4.0/jPlayer.Blue.Monday.2.4.0/blue.monday/jplayer.blue.monday.css', array('group' => CSS_THEME, 'every_page' => TRUE, 'scope' => 'header'));
    }
    DannysComedyClubRouteFactory::getRouteInstance()->htmlRenderVariables($vars);
}

function md_minimal_preprocess_page(&$vars, $hook) {
    $venues = entity_get_controller('venue')->readMultipleEntities(array(), array(), array(
        'node.status' => 1
    ));
    if(!empty($venues)) {
        $vars['header_sidebar'] = '';
        foreach($venues as $key => $venue) {
            $venue_uri = entity_uri('venue', $venue);
            $items = array(
                'content' => '<a class="underline" href="'.url($venue_uri['path'], array('base_url' => TRUE)).'">'.entity_label('venue', $venue).'</a>'
            );
            $venue->getAddress();
            $address = explode(',', $venue->getVenueAddress());
            $vars['header_sidebar'] .= theme('list_item_view', array(
                'ul_class' => 'unstyled',
                'li_class' => '',
                'items' => array($items)
            )) . '<div class="column_mini">' . $venue->getVenueAddress() . '</div>';
        }
    }
    $vars['follow_us'] = theme_get_setting('follow_us'); 
    $vars['share_on'] = theme_get_setting('share_on');

    $vars['secondary_menu'] = menu_navigation_links(variable_get('menu_secondary_links_source', 'menu-secondary-menu'));

    $vars['content_classes_array'] = array();
    if (drupal_is_front_page()) {
        $vars['accordion'] = theme_render_template(path_to_theme() . '/layouts/shows-accordion.php', array());
    }

    if (!empty($vars['page']['sidebar'])) {
        $vars['content_classes_array'][] = 'span8';
    } elseif (!empty($vars['page']['sidebar_mini'])) {
        $vars['content_classes_array'][] = 'span9';
    }
    DannysComedyClubRouteFactory::getRouteInstance()->pageRenderVariables($vars);
}

function md_minimal_preprocess_entity(&$vars) {
    DannysComedyClubRouteFactory::getRouteInstance()->entityRenderVariables($vars);
}

function md_minimal_process_page(&$vars) {
    $vars['content_classes'] = implode(' ', $vars['content_classes_array']);
}

function md_minimal_preprocess_node(&$vars) {
    DannysComedyClubRouteFactory::getRouteInstance()->nodeRenderVariables($vars);
}

function md_minimal_process_node(&$vars) {
    
}

function md_minimal_preprocess_field(&$vars) {
    DannysComedyClubRouteFactory::getRouteInstance()->fieldRenderVariables($vars);
}

function md_minimal_process_field(&$vars) {
    
}

function md_minimal_preprocess_region(&$vars) {
    if ($vars['region'] == 'sidebar') {
        $vars['classes_array'][] = 'span4';
    } elseif ($vars['region'] == 'sidebar_mini') {
        $vars['classes_array'][] = 'span3';
    }
}

function md_minimal_preprocess_block(&$vars, $hook) {
    // Add a striping class.
    $vars['classes_array'][] = 'block-' . $vars['zebra'];
    $vars['classes_array'][] = 'widget';
//    $menu_item = menu_get_item();
    DannysComedyClubRouteFactory::getRouteInstance()->blockRenderVariables($vars['block'], $vars);
}

function md_minimal_preprocess_taxonomy_term(&$vars) {
    DannysComedyClubRouteFactory::getRouteInstance()->taxonomyRenderVariables($vars);
}

function md_minimal_process_taxonomy_term(&$vars) {
    $vars['attributes'] = drupal_attributes($vars['attributes_array']);
    $vars['title_attributes'] = drupal_attributes($vars['title_attributes_array']);
}

function md_minimal_preprocess_comment(&$vars, $hook) {
    // Add a striping class.
    if ($vars['picture']) {
        $vars['classes_array'][] = 'withpicture';
    }
}

function md_minimal_breadcrumb(&$vars) {
    $breadcrumb = $vars['breadcrumb'];
    array_walk($breadcrumb, function(&$value, $index) {
        $value = htmlspecialchars_decode($value);
    });
    if (!empty($breadcrumb)) {
        $output = '<div class="breadcrumb-page column_small">' . implode(' › ', $breadcrumb) . '</div>';
        return $output;
    }
}

/* 	
 * 	Converts a string to a suitable html ID attribute.
 * 	
 * 	 http://www.w3.org/TR/html4/struct/global.html#h-7.5.2 specifies what makes a
 * 	 valid ID attribute in HTML. This function:
 * 	
 * 	- Ensure an ID starts with an alpha character by optionally adding an 'n'.
 * 	- Replaces any character except A-Z, numbers, and underscores with dashes.
 * 	- Converts entire string to lowercase.
 * 	
 * 	@param $string
 * 	  The string
 * 	@return
 * 	  The converted string
 */

function md_minimal_id_safe($string) {
    // Replace with dashes anything that isn't A-Z, numbers, dashes, or underscores.
    $string = strtolower(preg_replace('/[^a-zA-Z0-9_-]+/', '-', $string));
    // If the first character is not a-z, add 'n' in front.
    if (!ctype_lower($string{0})) { // Don't use ctype_alpha since its locale aware.
        $string = 'id' . $string;
    }
    return $string;
}

/**
 * Generate the HTML output for a menu link and submenu.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 *
 * @return
 *   A themed HTML string.
 *
 * @ingroup themeable
 */
function md_minimal_menu_link(array $variables) {
    $element = $variables['element'];
    $sub_menu = '';

    if ($element['#below']) {
        $sub_menu = drupal_render($element['#below']);
    }
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);
    // Adding a class depending on the TITLE of the link (not constant)
    $element['#attributes']['class'][] = md_minimal_id_safe($element['#title']);
    // Adding a class depending on the ID of the link (constant)
    $element['#attributes']['class'][] = 'mid-' . $element['#original_link']['mlid'];
    return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Override or insert variables into theme_menu_local_task().
 */
function md_minimal_preprocess_menu_local_task(&$variables) {
    $link = & $variables['element']['#link'];

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
        $link['title'] = check_plain($link['title']);
    }
    $link['localized_options']['html'] = TRUE;
    $link['title'] = '<span class="tab">' . $link['title'] . '</span>';
}

/*
 *  Duplicate of theme_menu_local_tasks() but adds clearfix to tabs.
 */

function md_minimal_menu_local_tasks(&$variables) {
    $output = '';

    if (!empty($variables['primary'])) {
        $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
        $variables['primary']['#prefix'] .= '<ul class="tabs primary clearfix">';
        $variables['primary']['#suffix'] = '</ul>';
        $output .= drupal_render($variables['primary']);
    }
    if (!empty($variables['secondary'])) {
        $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
        $variables['secondary']['#prefix'] .= '<ul class="tabs secondary clearfix">';
        $variables['secondary']['#suffix'] = '</ul>';
        $output .= drupal_render($variables['secondary']);
    }

    return $output;
}

function theme_view_element_wrapper($vars) {
    array_walk($vars['items'], function(&$item, $key) {
        $item = '<div class="clearfix">' . $item . '</div>';
    });
    return implode(' ', $vars['items']);
}