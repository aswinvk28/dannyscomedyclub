<?php 

if(!empty($performances)):

    if(isset($display_attributes)) { ?>

    <div class="<?php print $classes; ?>" <?php print $attributes; ?>>
    
    <?php }
    
    if(!empty($photos)): ?>

    <h4 class="column_small white">Performances:</h4>
    <div class="clearfix column_mini performances-masonry">

    <?php print render($photos); ?>

    </div>
    
    <?php endif;
    
    if(isset($display_attributes)) { ?>
    
    </div>

    <?php }

endif; ?>