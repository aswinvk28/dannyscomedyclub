<div class="clearfix">
    <div class="column_title align-center">
        <?php $field_view = field_view_field('node', $show->getNode(), 'field_date', 'show_performers_widget'); print drupal_render($field_view); ?>
    </div>
    <div class="row-fluid" itemscope itemtype="http://schema.org/Event">
        <?php if(!empty($performances)); ?>
        <table class="table table-bordered column_small white">
            <thead>
                <tr>
                    <th>Performers</th>
                    <th>Performing</th>
                </tr>
            </thead>
            <tbody>
                <?php
                
                foreach($performances as $performance) { 
                $performance_type = new PerformanceType($performance->getPerformanceType()); ?>
                
                <tr><td>

                <?php $node_uri = node_uri($performance->getPerformer()->getNode()); $node_url = drupal_lookup_path('alias', $node_uri['path']); 
                $tags = field_get_items('node', $performance->getPerformer()->getNode(), 'field_performer_tags');
                $print_tags = '';
                if(!empty($tags)):
                foreach($tags as $tag) {
                    $print_tags .= taxonomy_term_title(taxonomy_term_load($tag['tid']));
                }
                endif;
                if($print_tags == '') $print_tags = $performance_type->getPerformingType();
                ?>
                    <a itemprop="performer" href="<?php echo $node_url ? base_path() . $performance->getPerformer()->getNode()->type . '/' . $node_url : 'javascript:void(0)'; ?>" class="bootstrap_title" 
                title="<?php echo $print_tags; ?>" 
                data-original-title="<?php echo $print_tags; ?>"><?php echo node_page_title($performance->getPerformer()->getNode()); ?></a>

                </td>
                
                <td>
                    
                    <?php 
                    print $performance_type->viewPerformanceType(); ?>
                    
                </td></tr>

                <?php }
                ?>
            </tbody>
        </table>
    </div>
</div>