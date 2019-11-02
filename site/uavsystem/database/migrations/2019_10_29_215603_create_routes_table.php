<?php

use Illuminate\Support\Facades\Schema;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateRoutesTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('routes', function (Blueprint $table) {
            $table->increments('id');

            $table->integer('uav_id')->unsigned();
            $table->foreign('uav_id')
            ->references('id')->on('uavs')
            ->onDelete('cascade');

            $table->integer('in_if_id')->unsigned()->nullable();
            $table->foreign('in_if_id')
            ->references('id')->on('devices')
            ->onDelete('cascade');

            $table->integer('in_tag_id')->unsigned()->nullable();
            $table->foreign('in_tag_id')
            ->references('id')->on('mpls_tags')
            ->onDelete('cascade');

            $table->integer('out_if_id')->unsigned()->nullable();
            $table->foreign('out_if_id')
            ->references('id')->on('devices')
            ->onDelete('cascade');


            $table->integer('out_tag_id')->unsigned()->nullable();
            $table->foreign('out_tag_id')
            ->references('id')->on('mpls_tags')
            ->onDelete('cascade');
            
            $table->timestamps();
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('routes');
    }
}
