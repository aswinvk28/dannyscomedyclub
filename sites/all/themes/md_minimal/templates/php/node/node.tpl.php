<article class="<?php print $classes; ?>" <?php echo $attributes; ?>>
    
  <?php print render($title_prefix); ?>
    <h3<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h3>
  <?php print render($title_suffix); ?>
	
  <div class="content">
    <?php 
      print render($content);
     ?>
  </div>
    
</article> <!-- /node-->