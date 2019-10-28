<?php

use Illuminate\Support\Facades\Schema;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateUavsTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('uavs', function (Blueprint $table) {
            $table->increments('id');
            $table->string('name');
            $table->string('local_ip')->unique();
            $table->integer('network_in_id')->unsigned()->nullable();
            $table->foreign('network_in_id')
            ->references('id')->on('networks')
            ->onDelete('cascade');
            $table->integer('network_out_id')->unsigned()->nullable();
            $table->foreign('network_out_id')
            ->references('id')->on('networks')
            ->onDelete('cascade');
            $table->integer('tag_in_id')->unsigned();
            $table->foreign('tag_in_id')
            ->references('id')->on('mpls_tags')
            ->onDelete('cascade');
            $table->integer('tag_out_id')->unsigned();
            $table->foreign('tag_out_id')
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
        Schema::dropIfExists('uavs');
    }
}
