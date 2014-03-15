<?php $show = ShowFactory::getShowInstance(); ?>

<li class="bootstrap_title" title="<?php echo $show->printStatus(); ?>" data-original-title="<?php echo $show->printStatus(); ?>" <?php print $attributes; ?>>
    <?php 
    if($node_url !== $uri_path) : ?>
    <a href="<?php echo $node_url; ?>">
    <?php endif; ?>
        <div class="<?php echo $show->printClass($node_url); ?>" <?php print $title_attributes; ?>>
        <?php echo $title; ?>
            <span class="badge badge-inverse">&nbsp;&nbsp;<?php echo $show->printStatus(); ?></span>
        </div>
    <?php if($node_url !== $uri_path) : ?>
    </a>
    <?php endif; ?>
</li>