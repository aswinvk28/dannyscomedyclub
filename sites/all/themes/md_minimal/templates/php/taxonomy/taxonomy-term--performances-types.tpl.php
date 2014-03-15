<div class="<?php print $classes; ?>">

    <?php
    if($view_mode == 'artistes_performance_types') { ?>
    
    <span <?php print $attributes; ?>>
        <span <?php print $title_attributes; ?>><?php print $term_name; ?></span>
    </span>
    
    <?php } else { ?>
    
    <div class="content" <?php print $attributes; ?>>
        
        <?php $perf_type = new PerformanceType($term); 
        $view = $perf_type->viewPerformances(); ?>
        
        <?php if(!empty($view['clips'])): ?>
        
        <h4 class="column_small white">Clips:</h4>
        <div class="clearfix column_mini performance-clips-masonry">

        <?php print render($view['clips']); ?>

        </div>

        <?php endif; ?>

        <?php if(!empty($view['photos'])): ?>

        <h4 class="column_small white">Snaps:</h4>
        <div class="clearfix column_mini performances-masonry">

        <?php print render($view['photos']); ?>

        </div>

        <?php endif; ?>

    </div>

    <?php } ?>   
    
</div>
    
