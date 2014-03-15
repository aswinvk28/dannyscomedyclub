<aside class="<?php print $classes; ?> clearfix" <?php print $attributes; ?>>
    
    <?php print render($title_prefix); ?>
    <?php if ($block->subject): ?>
    <header class="column_title">
    	<h4 class="block-title"<?php print $title_attributes; ?>><?php print $block->title; ?></h4>
    </header>
    <?php endif;?>
    <?php print render($title_suffix); ?>
		
	<?php if(!empty($top_block_content)) : ?>
	<div class="top_block_content column_small white">
            <?php print render($top_block_content); ?>
	</div>
	<?php endif; ?>
	
	<div class="content column_small" <?php print $content_attributes; ?>>
	  <?php print $content; ?>
	</div>
    
        <?php if(!empty($bottom_block_content)) : ?>
	<div class="bottom_block_content column_small white">
            <?php print render($bottom_block_content); ?>
	</div>
	<?php endif; ?>

</aside> <!-- /block -->